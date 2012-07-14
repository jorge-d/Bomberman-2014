#ifndef __SPEED_BONUS_HH__
# define __SPEED_BONUS_HH__

#include "AElement.hh"

namespace bomberman
{
  class SpeedBonus : public AElement
  {
  public:
    SpeedBonus(GameEngine *, int, int);
    ~SpeedBonus(void);
    bool refresh(void);
  };
}

#endif
