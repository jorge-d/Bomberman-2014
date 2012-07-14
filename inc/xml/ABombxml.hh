#ifndef _ABOMBXML_H
# define _ABOMBXML_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include "tinyxml.h"
#include "Color.hpp"
#include "AElement.hh"
#include "Exception.hh"

namespace bomberman{


  struct coords{
    unsigned int x;
    unsigned int y;
    unsigned int bombRange;
    float speed;
    gdl::Color color;
    unsigned int score;
    unsigned int bag;
    elemType type;
    enum bomberman::elemType t;
  };

  class ABombxml
  {
  public:

    ABombxml(std::string const &);
    virtual ~ABombxml();

    virtual bool isOk() const = 0;
    virtual std::list<bomberman::coords*> const &getList() const;
    virtual std::vector<std::vector<bool> > const &getMap() const;
    virtual std::string const &getMapName() const;
    virtual unsigned int getNbSpawns() const;
    virtual unsigned int getHeight() const;
    virtual unsigned int getWidth() const;

  protected:
    virtual void loadFile();

    virtual bool addPWalls();
    virtual bool addBWalls();

    TiXmlDocument doc;

    std::list<bomberman::coords*> l;
    std::vector<std::vector<bool> > v;
    unsigned int  width;
    unsigned int  height;
    unsigned int  nbSpawns;
    std::string  filename;
    std::string  mapName;
    bool ok;

  };

}

#endif
