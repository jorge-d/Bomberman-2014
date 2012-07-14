#include "LoadMap.hh"

namespace bomberman
{
  LoadMap::LoadMap(std::string const &s) : ABombxml(s)
  {
    try
      {
	loadFile();
	this->ok = gettingMap();
      }
    catch (Exception &e)
      {
	this->ok = false;
	std::cerr << e.what() << std::endl;
      }
  }

  LoadMap::~LoadMap()
  {
  }

  bool LoadMap::isOk(void) const
  {
    return (this->ok);
  }


  bool LoadMap::addPlayers()
  {
    TiXmlElement *players;
    if ((players = this->doc.FirstChildElement("players")) == NULL)
      return (false);
    TiXmlElement *player;
    if ((player = players->FirstChildElement()) == NULL)
      return (false);
    unsigned int i = 0;
    int nb;
    players->QueryIntAttribute("nb", &nb);
    this->nbSpawns = nb;
    while (player)
      {
	bomberman::coords *coords = new bomberman::coords();
	int x = 0, y = 0;
	player->QueryIntAttribute("x", &x);
	player->QueryIntAttribute("y", &y);
	coords->x = x;
	coords->y = y;
	++coords->x;
	++coords->y;
	coords->t = SPAWN;
	if (x < 0 || coords->x >= this->width - 1 ||
	    y < 0 || coords->y >= this->height - 1)
	  throw Exception("Bad coords for map creation");
	if (this->v[coords->x][coords->y] != false)
	  return false;
	this->l.push_back(coords);
	this->v[coords->x][coords->y] = true;
	++i;
	player = player->NextSiblingElement();
      }
    if (i == this->nbSpawns && this->nbSpawns >= Constants::MinNbPlayers)
      return true;
    return false;
  }

  bool LoadMap::gettingMap(void)
  {
    TiXmlElement *map;
    if ((map = this->doc.FirstChildElement("map")) == NULL)
      return false;
    int w = 0, h = 0;
    map->QueryIntAttribute("x", &w);
    this->width = w;
    map->QueryIntAttribute("y", &h);
    this->height = h;
    this->mapName = map->Attribute("name");
    if (this->width < Constants::MinWidth || this->height < Constants::MinHeight)
      return false;
    this->width += 2;
    this->height += 2;
    this->v.reserve(this->width);
    for (unsigned int i = 0; i < this->width; ++i)
      {
	this->v.push_back(std::vector<bool>());
	this->v[i].reserve(this->height);
	for (unsigned int j = 0; j < this->height; ++j)
	  this->v[i][j] = false;
      }
    return (addPlayers() &&
	    addPWalls() &&
	    addBWalls());
  }

}
