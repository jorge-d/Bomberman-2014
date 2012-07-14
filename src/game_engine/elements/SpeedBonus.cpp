#include "SpeedBonus.hh"

namespace bomberman
{
  SpeedBonus::SpeedBonus(GameEngine *e, int x, int y) :
    AElement(e, x, y, SPEED_BONUS)
  {
  }

  SpeedBonus::~SpeedBonus(void)
  {
  }

  bool SpeedBonus::refresh(void)
  {
    return this->isAlive();
  }
}
