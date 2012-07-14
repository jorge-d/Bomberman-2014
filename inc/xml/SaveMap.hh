#ifndef _SMAP_H
# define _SMAP_H

#include <map>
#include <tinyxml.h>
#include "APlayer.hh"
#include "Map.hh"

namespace bomberman
{
  class SaveMap
  {
  public:

    SaveMap(Map const &, std::string const &);
    ~SaveMap(void);
    typedef void (SaveMap::*ptr)(AElement*, int, int);
    bool isOk(void) const;

  private :
    void mapToXml();
    void WriteInXml(std::string const &filename);

    void fillPlayer(std::list<APlayer *> &p);
    void fillBWall(AElement*, int x, int y);
    void fillPWall(AElement*, int x, int y);
    void fillBonus(AElement* e, int x, int y);

    void link(std::string const &, std::list<TiXmlElement*> &);
    void linkPlayers(void);

    TiXmlDocument doc;
    std::string const &name;

    Map const & map_;
    static int v;
    bool ok;
    std::map<elemType, SaveMap::ptr> smap_;
    std::list<TiXmlElement *> plist_;
    std::list<TiXmlElement *> blist_;
    std::list<TiXmlElement *> pwlist_;
    std::list<TiXmlElement *> bwlist_;
    unsigned int height;
    unsigned int width;
  };
}

#endif
