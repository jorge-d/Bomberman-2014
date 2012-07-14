#ifndef __FLAME_CLASS_HH__
# define __FLAME_CLASS_HH__

#include "APlayer.hh"

namespace bomberman
{
  class GameEngine;

  class Flame : public AElement
  {
  private:
    APlayer &p_;
    int range_;
    int nextX_;
    int nextY_;
    bool spread_;

  public:
    Flame(GameEngine *, APlayer&, int, int, int, Direction = NONE);
    ~Flame(void);
    bool refresh(void);
  };
}

#endif
