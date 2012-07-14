#ifndef _LOADM_H
# define _LOADM_H

#include "ABombxml.hh"

namespace bomberman
{
  class LoadMap : public ABombxml
  {
  public :
    LoadMap(std::string const&);
    ~LoadMap();
    bool isOk(void) const;
  private :

    bool addPlayers(void);
    bool gettingMap(void);
  };
}

#endif
