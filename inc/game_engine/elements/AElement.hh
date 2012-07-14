#ifndef AELEMENT_HH__
# define AELEMENT_HH__

#include "Constants.hh"

namespace bomberman
{
  enum Direction
    {
      UP,
      LEFT,
      RIGHT,
      DOWN,
      NONE
    };

  enum elemType
    {
      HUMAN,
      IA,
      BOMB,
      BREAKABLE_WALL,
      PERMANENT_WALL,
      FLAME,
      RANGE_BONUS,
      BAG_BONUS,
      SPEED_BONUS,
      SPAWN
    };

  class GameEngine; // Forward declaration

  class AElement
  {
  protected:
    GameEngine *gameEngine_;

    unsigned int posX_;
    unsigned int posY_;
    elemType type_;
    Direction dir_;
    bool alive_;
    float timer_;

  public:
    AElement(GameEngine *, unsigned int, unsigned int, elemType, Direction = NONE);
    virtual ~AElement(void);

    elemType getType(void) const;
    unsigned int getPosX(void) const;
    unsigned int getPosY(void) const;
    bool isAlive(void) const;
    Direction getDirection(void) const;

    virtual bool refresh(void) = 0;
    virtual void kill(void);
  };
}
#endif /* AELEMENT_HH__ */
