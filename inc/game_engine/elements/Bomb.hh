#ifndef __BOMB_CLASS_HH__
# define __BOMB_CLASS_HH__

#include "AElement.hh"
#include "APlayer.hh"

namespace bomberman
{
  class GameEngine;

  class Bomb : public AElement
  {
  private:
    int range_;
    APlayer &p_;

  private:
    void createFlame(unsigned int, unsigned int, unsigned int, Direction);

  public:
    Bomb(GameEngine *, int, int, int, APlayer&);
    ~Bomb(void);
    bool refresh(void);
    void kill(void);
  };
}

#endif
