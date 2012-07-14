#include "LuaException.hh"
#include "Map.hh"
#include "Computer.hh"
#include "Exception.hh"

namespace bomberman
{
  unsigned int Computer::nbIAs = 0;

  Computer::Computer(GameEngine *e, int x, int y)
    : APlayer(e, x, y, IA), game_engine_(e), is_good_(true)
  {
    this->lua_.setFile("scripts/ia.lua");
    try
      {
	this->lua_.load();
      }
    catch (lua::LuaException e)
      {
	std::cerr << e.what() << std::endl;
	this->is_good_ = false;
	//throw Exception("Error loading IA");
      }
    Computer::nbIAs++;
    this->actionsP_[LEFT] = &Computer::moveLeft;
    this->actionsP_[RIGHT] = &Computer::moveRight;
    this->actionsP_[UP] = &Computer::moveUp;
    this->actionsP_[DOWN] = &Computer::moveDown;
  }

  Computer::~Computer(void)
  {
    Computer::nbIAs--;
  }

  void Computer::moveLeft(void)
  {
    int x = this->getPosX() - 1;
    int y = this->getPosY();
    this->move(x, y, LEFT);
  }

  void Computer::moveRight(void)
  {
    int x = this->getPosX() + 1;
    int y = this->getPosY();
    this->move(x, y, RIGHT);
  }

  void Computer::moveUp(void)
  {
    int x = this->getPosX();
    int y = this->getPosY() - 1;
    this->move(x, y, UP);
  }

  void Computer::moveDown(void)
  {
    int x = this->getPosX();
    int y = this->getPosY() + 1;
    this->move(x, y, DOWN);
  }

  std::string* Computer::mapToStringTab(void)
  {
    Map *map = this->game_engine_->getMap();
    int width = static_cast<int>(map->getWidth());
    int height = static_cast<int>(map->getHeight());
    int posx = static_cast<int>(this->getPosX());
    int posy = static_cast<int>(this->getPosY());
    std::string *new_map = new std::string[30];
    std::list<APlayer *> p;
    AElement *t;
    int real_y = 0;

    for (int y = posy - 15; y < posy + 15; y++)
      {
	for (int x = posx - 15; x < posx + 15; x++)
	  {
	    if (x < 0 || x >= width || y < 0 || y >= height)
	      new_map[real_y] += static_cast<char>(PERMANENT_WALL) + '0';
	    else if ((t = map->recoverObjectAt(x, y)))
	      new_map[real_y] += static_cast<char>(t->getType()) + '0';
	    else if (map->recoverPlayerAt(p, x, y))
	      {
		while (!p.empty())
		  p.pop_front();
		new_map[real_y] += '1';
	      }
	    else
	      new_map[real_y] += '0';
	  }
	++real_y;
      }
    return new_map;
  }

  bool Computer::refresh(void)
  {
    if (this->is_good_ && this->gameEngine_->getElapsedTime() - this->timer_ > this->speed_)
      {
	Direction dir;
	std::string *new_map;
	int xpos = 15;
	int ypos = 15;

	this->lua_.getGlobal("exec_ia");
	new_map = this->mapToStringTab();
	this->lua_.pushStringTable(new_map, 30);
	this->lua_.pushInteger(xpos);
	this->lua_.pushInteger(ypos);
	try
	  {
	    this->lua_.pcall(3, 1, 0);
	    dir = (Direction)this->lua_.toNumber(-1);
	    if (dir == 4)
	      this->setBomb();
	    else if (this->actionsP_[dir])
	      (this->*(this->actionsP_[dir]))();
	  }
	catch (lua::LuaException e)
	  {
	    std::cerr << e.what() << std::endl;
	  }
	delete[] new_map;
      }
    return this->isAlive();
  }

  unsigned int Computer::getNbIAs(void)
  {
    return Computer::nbIAs;
  }
}
