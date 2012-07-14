#ifndef __RANGE_BONUS_HH__
# define __RANGE_BONUS_HH__

#include "AElement.hh"

namespace bomberman
{
  class RangeBonus : public AElement
  {
  public:
    RangeBonus(GameEngine *, int, int);
    ~RangeBonus(void);
    bool refresh(void);
  };
}

#endif
