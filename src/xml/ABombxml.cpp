#include <iostream>
#include <sstream>
#include "ABombxml.hh"

namespace bomberman
{
  ABombxml::ABombxml(std::string const &s) : doc(s.c_str()), filename(s)
  {
  }

  ABombxml::~ABombxml()
  {
    std::list<coords *>::iterator it = this->l.begin();

    for ( ; it != this->l.end(); ++it)
      delete (*it);
  }

  bool ABombxml::isOk() const
  {
    return (this->ok);
  }

  void ABombxml::loadFile()
  {
    if (!this->doc.LoadFile())
      throw Exception(this->doc.ErrorDesc());
  }

  std::vector<std::vector<bool> > const &ABombxml::getMap() const
  {
    return (this->v);
  }

  std::string const &ABombxml::getMapName() const
  {
    return (this->mapName);
  }

  unsigned int ABombxml::getNbSpawns() const
  {
    return (this->nbSpawns);
  }

  unsigned int ABombxml::getHeight() const
  {
    return (this->height);
  }

  unsigned int ABombxml::getWidth() const
  {
    return (this->width);
  }

  std::list<bomberman::coords*> const &ABombxml::getList() const
  {
    return (this->l);
  }

  bool ABombxml::addBWalls()
  {
    const TiXmlElement *bwalls = this->doc.FirstChildElement("bwalls");
    if (bwalls  == NULL)
      return true;
    const TiXmlElement *bwall = bwalls->FirstChildElement();
    if (bwall == NULL)
      return false;
    unsigned int i = 0;

    while (bwall)
      {
	bomberman::coords *coords = new bomberman::coords();
	int x = 0, y = 0;
	bwall->QueryIntAttribute("x", &x);
	bwall->QueryIntAttribute("y", &y);
	coords->x = x;
	coords->y = y;
	++coords->x;
	++coords->y;
	coords->t = BREAKABLE_WALL;
	if (x < 0 || coords->x >= this->width - 1 ||
	    y < 0 || coords->y >= this->height - 1)
	  throw Exception("bad coords for map creation");
	if (this->v[coords->x][coords->y] != false)
	  return false;
	this->l.push_back(coords);
 	this->v[coords->x][coords->y] = true;
	++i;
	bwall = bwall->NextSiblingElement();
      }
    return true;
  }

  bool ABombxml::addPWalls()
  {
    const TiXmlElement *pwalls = this->doc.FirstChildElement("pwalls");
    if (pwalls == NULL)
      return true;
    const TiXmlElement *pwall = pwalls->FirstChildElement();
    if (pwall == NULL)
      return false;
    unsigned int i = 0;
    while (pwall)
      {
	bomberman::coords *coords = new bomberman::coords();
	int x = 0, y = 0;
	pwall->QueryIntAttribute("x", &x);
	pwall->QueryIntAttribute("y", &y);
	coords->x = x;
	coords->y = y;
	++coords->x;
	++coords->y;
	coords->t = PERMANENT_WALL;
	if (x < 0 || coords->x >= this->width - 1 ||
	    y < 0 || coords->y >= this->height - 1)
	  throw Exception("bad coords for map creation");
	if (this->v[coords->x][coords->y] != false)
	  return false;
	this->l.push_back(coords);
	this->v[coords->x][coords->y] = true;
	++i;
	pwall = pwall->NextSiblingElement();
      }
    return true;
  }
}
