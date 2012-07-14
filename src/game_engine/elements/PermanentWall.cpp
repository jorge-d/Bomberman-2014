#include "PermanentWall.hh"

namespace bomberman
{
  PermanentWall::PermanentWall(GameEngine *e, int x, int y) :
    AElement(e, x, y, PERMANENT_WALL)
  {
  }

  PermanentWall::~PermanentWall(void)
  {
  }

  bool PermanentWall::refresh(void)
  {
    return true;
  }

  void PermanentWall::kill(void)
  {
  }
}
