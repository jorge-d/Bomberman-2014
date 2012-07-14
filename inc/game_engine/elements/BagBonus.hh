#ifndef __BAG_BONUS_HH__
# define __BAG_BONUS_HH__

#include "AElement.hh"

namespace bomberman
{
  class BagBonus : public AElement
  {
  public:
    BagBonus(GameEngine *, int, int);
    ~BagBonus(void);
    bool refresh(void);
  };
}

#endif
