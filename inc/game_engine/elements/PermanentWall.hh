#ifndef _PERMANENTWALL_HH__
# define _PERMANENTWALL_HH__

#include "AElement.hh"

namespace bomberman
{
  class GameEngine;

  class PermanentWall : public AElement
  {
  public:
    PermanentWall(GameEngine *, int, int);
    ~PermanentWall(void);
    bool refresh(void);
    void kill(void);
  };
}


#endif
