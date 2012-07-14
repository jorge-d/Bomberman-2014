#ifndef __BREAKABLE_WALL_HH__
# define __BREAKABLE_WALL_HH__

#include "AElement.hh"

namespace bomberman
{
  class GameEngine;

  class BreakableWall : public AElement
  {
  public:
    BreakableWall(GameEngine *, int, int);
    ~BreakableWall(void);
    bool refresh(void);
    void kill(void);
  };
}

#endif
