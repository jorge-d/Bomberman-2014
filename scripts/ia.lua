-- Constants
UP, LEFT, RIGHT, DOWN, SET_BOMB, NONE = 0, 1, 2, 3, 4, 5

EMPTY, PLAYER, BOMB, BWALL, WALL, FLAME, RANGE_BONUS, BAG_BONUS, SPEED_BONUS
   = 48, 49, 50, 51, 52, 53, 54, 55, 56

gl_last_mv = UP

-- Easy map acces
function element_at(map, y, x)
   return string.byte(map[y + 1], x + 1);
end

-- Search ne nearest elem
function get_nearest_element(map, x, y, elem)
   ytmp = -1
   xtmp = -1
   for yl = 0, #map - 1 do
      for xl = 0, #map[yl + 1] - 1 do
	 if (element_at(map, yl, xl) == elem
	  and (math.abs(x - xl) + math.abs(y - yl) < math.abs(x - xtmp) + math.abs(y - ytmp) or (xtmp == -1 and ytmp == -1)) and (x ~= xl or y ~= yl or elem ~= PLAYER)) then
--	    io.write("x: "..xl.." y: "..yl.."\n")
	    xtmp = xl
	    ytmp = yl
	 end
      end
   end
   return xtmp, ytmp
end

-- check bonus
function check_bonus(map, x, y)
   if (element_at(map, y, x) == RANGE_BONUS
    or element_at(map, y, x) == SPEED_BONUS or element_at(map, y, x) == BAG_BONUS) then
      return true
   end
   return false
end

-- check move
function check_move(map, x, y)
   if (check_bonus(map, x, y) or element_at(map, y, x) == EMPTY) then
      return true
   end
   return false
end

-- Avoid bombs
function avoid_bombs(map, x, y, xdest, ydest)
   xbomb, ybomb = get_nearest_element(map, x, y, BOMB)

   if (ybomb == y and math.abs(x - xbomb) < 5) then
      if (check_move(map, x, y + 1)) then
	 return x, y + 1
      elseif (check_move(map, x, y - 1)) then
	 return x, y - 1
      elseif (xbomb >= x and check_move(map, x - 1, y)) then
	 return x - 1, y
      elseif (xbomb < x and check_move(map, x + 1, y)) then
	 return x + 1, y
      end
   end

   if (xbomb == x and math.abs(y - ybomb) < 5) then
      if (check_move(map, x + 1, y)) then
	 return x + 1, y
      elseif (check_move(map, x - 1, y)) then
	 return x - 1, y
      elseif (ybomb >= y and check_move(map, x, y - 1)) then
	 return x, y - 1
      elseif (ybomb < y and check_move(map, x, y + 1)) then
	 return x, y + 1
      end
   end

   return xdest, ydest
end

function check_bomb_vertical(map, x, y)
   xbomb, ybomb = get_nearest_element(map, x, y, BOMB)
   xflame, yflame = get_nearest_element(map, x, y, FLAME)
   if ((xbomb == x and math.abs(y - ybomb) < 5)
    or (xflame == x)) then
    return true
   end
   return false
end

function check_bomb_horizontal(map, x, y)
   xbomb, ybomb = get_nearest_element(map, x, y, BOMB)
   xflame, yflame = get_nearest_element(map, x, y, FLAME)
   if ((ybomb == y and math.abs(x - xbomb) < 5)
    or (yflame == y))then
      return true
   end
   return false
end

-- Check bombs
function check_bombs(map, x, y)
   if (check_bomb_horizontal(map, x, y) or check_bomb_vertical(map, x, y)) then
      return true
   end
   return false
end

-- Find longest way
function get_longest_way(map, x, y)
   direction = DOWN
   down = 0;
   for i = y + 1, #map - 1 do
      if check_move(map, x, i) == false and check_bomb_horizontal(map, x, i) == false then
	 break
      end
      down = down + 1
   end
   max = down
   up = 0;
   for i = y - 1, 0, -1 do
      if check_move(map, x, i) == false and check_bomb_horizontal(map, x, i) == false then
	 break
      end
      up = up + 1
   end
   if up >= max then
      direction = UP
      max = up
   end
   left = 0;
   for i = x - 1, #map[y] - 1 do
      if check_move(map, i, y) == false and check_bomb_vertical(map, i, y) == false then
	 break
      end
      left = left + 1
   end
   if left >= max then
      direction = LEFT
      max = left
   end
   right = 0;
   for i = x + 1, 0, -1 do
      if check_move(map, i, y) == false and check_bomb_vertical(map, i, y) == false then
	 break
      end
      right = right + 1
   end
   if right >= max then
      direction = RIGHT
   end
--   io.write("left = "..left.." down = "..down.." right = "..right.." up = "..up.."\n")
   return direction
end

-- get th sign of an expression
function get_sign(expr)
   if (expr < 0) then
      return -1
   else
      return 1
   end
end

-- check empty line betwen two players
function check_line(map, x, y, xp, yp)
   if (x == xp) then
      for i = y, yp, get_sign(yp - y) do
	 if (element_at(map, i, x) ~= EMPTY and element_at(map, i, x) ~= PLAYER) then
	    return false
	 end
      end
   elseif (y == yp) then
      for i = x, xp, get_sign(xp - x) do
	 if (element_at(map, y, i) ~= EMPTY and element_at(map, y, i) ~= PLAYER) then
	    return false
	 end
      end
   else
      return false
   end
   return true
end

-- Find the direction
function get_direction(map, x, y, xdest, ydest)
   if (element_at(map, y, x) == BOMB) then
      return (get_longest_way(map, x, y))
   end

   xp, yp = get_nearest_element(map, x, y, PLAYER)

   if (xp ~= -1 and ((xp == x and math.abs(yp - y) < 3)
		  or (yp == y and math.abs(xp - x) < 3)) and check_line(map, x, y, xp, yp) and check_bombs(map, x, y) == false) then
      return SET_BOMB
   end

   if ((element_at(map, y, x - 1) == PLAYER or element_at(map, y, x + 1) == PLAYER or element_at(map, y + 1, x) == PLAYER  or element_at(map, y - 1, x) == PLAYER) and check_bombs(map, x, y) == false) then
      return SET_BOMB
   end

   if (xp == -1 and yp == -1 and (element_at(map, y, x - 1) == BWALL or element_at(map, y, x + 1) == BWALL or element_at(map, y + 1, x) == BWALL  or element_at(map, y - 1, x) == BWALL) and check_bombs(map, x, y) == false) then
      return SET_BOMB
   end
   
   if (x > xdest) then
      if (check_move(map, x - 1, y) and check_bomb_vertical(map, x - 1, y) == false) then
	 return (LEFT)
      elseif (element_at(map, y, x - 1) == BWALL and check_bombs(map, x, y) == false) then
         return (SET_BOMB)
      end
   end
   if (y < ydest) then
      if (check_move(map, x, y + 1) and check_bomb_horizontal(map, x, y + 1) == false) then
	 return (DOWN)
      elseif (element_at(map, y + 1, x) == BWALL and check_bombs(map, x, y) == false) then
	 return (SET_BOMB)
      end
   end
   if (x < xdest) then
      if (check_move(map, x + 1, y) and check_bomb_vertical(map, x + 1, y) == false) then
	 return (RIGHT)
      elseif (element_at(map, y, x + 1) == BWALL and check_bombs(map, x, y) == false) then
         return (SET_BOMB)
      end
   end
   if (y > ydest) then
      if (check_move(map, x, y - 1) and check_bomb_horizontal(map, x, y - 1) == false) then
	 return (UP)
      elseif (element_at(map, y + 1, x) == BWALL and check_bombs(map, x, y) == false) then
	 return (SET_BOMB)
      end
   end
   if (math.abs(x - xdest) == 1 or math.abs(y - ydest) == 1 or x == xdest or y == ydest) then
      rd = math.random(0, 3)
      if (rd == UP and check_move(map, x, y - 1) and check_bomb_vertical(map, x, y - 1) == false) then
	 return (UP)
      end
      if (rd == DOWN and check_move(map, x, y + 1) and check_bomb_vertical(map, x, y + 1) == false) then
	 return (DOWN)
      end
      if (rd == LEFT and check_move(map, x - 1, y) and check_bomb_vertical(map, x - 1, y) == false) then
	 return (LEFT)
      end
      if (rd == RIGHT and check_move(map, x + 1, y) and check_bomb_vertical(map, x + 1, y) == false) then
	 return (RIGHT)
      end
   end
   return NONE
end

function exec_ia(map, x, y)
  -- for k, line in ipairs(map)
  -- do
  --    io.write(line.."\n")
  -- end
  -- io.write("x : "..x.." y : "..y.."\n")

   xdest, ydest = get_nearest_element(map, x, y, PLAYER)
   xbdest, ybdest = get_nearest_element(map, x, y, BAG_BONUS)
   if xbdest == -1 and ybdest == -1 then
      xbdest, ybdest = get_nearest_element(map, x, y, RANGE_BONUS)
      if xbdest == -1 and ybdest == -1 then
	 xbdest, ybdest = get_nearest_element(map, x, y, SPEED_BONUS)
	 if xbdest == -1 and ybdest == -1 and xdest == -1 and ydest == -1 then
	    xbdest, ybdest = get_nearest_element(map, x, y, BWALL)
	 end
      end
   end
   if xbdest ~= -1 and ybdest ~= -1 and (math.abs(xbdest - x) < math.abs(xdest - x) or math.abs(ybdest - y) < math.abs(ydest - y)) then
      xdest = xbdest
      ydest = ybdest
   end
   xdest, ydest = avoid_bombs(map, x, y, xdest, ydest)
   if (xdest == -1 and ydest == -1) then
      return math.random(0, 3)
   end
   gl_last_mv = get_direction(map, x, y, xdest, ydest)
   return (gl_last_mv)
end
