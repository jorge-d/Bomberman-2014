#ifndef _LOADS_H
# define _LOADS_H

#include "ABombxml.hh"

namespace bomberman
{
  class LoadSave : public ABombxml
  {
  public:

    LoadSave(std::string const &);
    ~LoadSave();
    bool isOk(void) const;
  private:

    bool addBonus(void);
    bool addPlayers(void);
    bool gettingMap(void);
  };
}

#endif
