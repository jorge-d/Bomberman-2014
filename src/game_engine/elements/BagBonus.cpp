#include "BagBonus.hh"

namespace bomberman
{
  BagBonus::BagBonus(GameEngine *e, int x, int y) :
    AElement(e, x, y, BAG_BONUS)
  {
  }

  BagBonus::~BagBonus(void)
  {
  }

  bool BagBonus::refresh(void)
  {
    return this->isAlive();
  }
}
