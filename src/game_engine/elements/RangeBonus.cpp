#include "RangeBonus.hh"

namespace bomberman
{
  RangeBonus::RangeBonus(GameEngine *e, int x, int y) :
    AElement(e, x, y, RANGE_BONUS)
  {
  }

  RangeBonus::~RangeBonus(void)
  {
  }

  bool RangeBonus::refresh(void)
  {
    return this->isAlive();
  }
}
