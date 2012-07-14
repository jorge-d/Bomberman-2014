#include "LoadSave.hh"

namespace bomberman
{

  LoadSave::LoadSave(std::string const &s) :  ABombxml(s)
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

  LoadSave::~LoadSave()
  {
  }

  bool LoadSave::isOk(void) const
  {
    return (this->ok);
  }

  bool LoadSave::addBonus()
  {
    TiXmlElement *bonus;
    if ((bonus = this->doc.FirstChildElement("bonuses")) == NULL)
      return true;
    const TiXmlElement *b = bonus->FirstChildElement();
    unsigned int i = 0;
    if (b == NULL)
      return false;
    while (b)
      {
	bomberman::coords *coords = new bomberman::coords();
	int x = 0, y = 0, type = 0;
	b->QueryIntAttribute("x", &x);
	b->QueryIntAttribute("y", &y);
	b->QueryIntAttribute("type", &type);
	coords->x = x;
	coords->y = y;
	++coords->x;
	++coords->y;
	coords->t = static_cast<elemType>(type);
	if (x < 0 || coords->x >= this->width - 1 ||
	    y < 0 || coords->y >= this->height - 1)
	  throw Exception("bad coords for map creation");
	if (this->v[coords->x][coords->y] != false)
	  return false;
	this->l.push_back(coords);
	this->v[coords->x][coords->y] = true;
	++i;
	b = b->NextSiblingElement();
      }
    return true;
  }

  bool LoadSave::addPlayers()
  {
    TiXmlElement *players;
    if ((players = this->doc.FirstChildElement("players")) == NULL)
      return (false);
    TiXmlElement *player;
    if ((player = players->FirstChildElement()) == NULL)
      return (false);
    unsigned int i = 0;
    int nb;
    if (players == NULL || player == NULL)
      return false;
    players->QueryIntAttribute("nb", &nb);
    this->nbSpawns = nb;
    while (player)
      {
	bomberman::coords *coords = new bomberman::coords();
	int x = 0, y = 0, bombRange = 0,  score = 0, bag = 0, type = 0;
	float speed = 0;
	int a = 255, r = 0, g = 0, b = 0;
	player->QueryIntAttribute("x", &x);
	player->QueryIntAttribute("y", &y);
	player->QueryIntAttribute("type", &type);
	player->QueryIntAttribute("bombRange", &bombRange);
	player->QueryFloatAttribute("speed", &speed);
	player->QueryIntAttribute("color_a", &a);
	player->QueryIntAttribute("color_r", &r);
	player->QueryIntAttribute("color_g", &g);
	player->QueryIntAttribute("color_b", &b);
	player->QueryIntAttribute("score", &score);
	player->QueryIntAttribute("bag", &bag);
	coords->x = x;
	coords->y = y;
	coords->bombRange = bombRange;
	coords->speed = speed;
	coords->color.a = a;
	coords->color.r = r;
	coords->color.g = g;
	coords->color.b = b;
	coords->score = score;
	coords->bag = bag;
	++coords->x;
	++coords->y;
	coords->t = static_cast<elemType>(type);
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

  bool LoadSave::gettingMap()
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
	    addBWalls() &&
	    addPWalls() && addBonus());
  }
}
