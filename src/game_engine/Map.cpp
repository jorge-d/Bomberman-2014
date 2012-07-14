#include <time.h>

#include "Map.hh"
#include "BreakableWall.hh"
#include "Human.hh"
#include "RangeBonus.hh"
#include "BagBonus.hh"
#include "SpeedBonus.hh"
#include "Computer.hh"
#include "Exception.hh"

namespace bomberman
{
  Map::Map(GameEngine *e, ABombxml *tmp, unsigned int nb) :
    gameEngine_(e), nbIAsAlive_(0), nbPlayersAlive_(0)
  {
    srand(time(NULL));
    this->pWall_ = new PermanentWall(this->gameEngine_, 0, 0);
    if (!tmp)
      {
	do
	  {
	    this->width_ = (rand() % 25) + 15;
	    this->height_ = (rand() % 25) + 15;
	  }
	while (this->height_ % 2 == 0 || this->width_ % 2 == 0);
	this->loadRandomMap(nb);
      }
    else
      this->loadMap(tmp, nb);
  }

  Map::Map(GameEngine *e, ABombxml *tmp) :
    gameEngine_(e), nbIAsAlive_(0), nbPlayersAlive_(0)
  {
    srand(time(NULL));
    this->pWall_ = new PermanentWall(this->gameEngine_, 0, 0);
    this->loadSave(tmp);
  }

  Map::~Map(void)
  {
    for (std::list<AElement *>::iterator it = this->o_.begin(); it != this->o_.end(); ++it)
      delete (*it);
    this->o_.clear();
    for (std::list<APlayer *>::iterator it2 = this->p_.begin(); it2 != this->p_.end(); ++it2)
      delete (*it2);
    this->p_.clear();
    delete this->pWall_;
  }

  void Map::loadSave(ABombxml *xm)
  {
    const std::list<bomberman::coords*>& li = xm->getList();
    std::list<bomberman::coords*>::const_iterator it = li.begin();

    this->width_ = xm->getWidth();
    this->height_ = xm->getHeight();
    this->buildShapes();
    while (it != li.end())
      {
	if (this->coorHasError((*it)->x, (*it)->y))
	  throw Exception("Bad coordinates in LoadSave");

	switch ((*it)->t)
	  {
	  case BREAKABLE_WALL:
	    this->addObject(new BreakableWall(this->gameEngine_, (*it)->x, (*it)->y));
	    break;
	  case RANGE_BONUS:
	    this->addObject(new RangeBonus(this->gameEngine_, (*it)->x, (*it)->y));
	    break;
	  case BAG_BONUS:
	    this->addObject(new BagBonus(this->gameEngine_, (*it)->x, (*it)->y));
	    break;
	  case SPEED_BONUS:
	    this->addObject(new SpeedBonus(this->gameEngine_, (*it)->x, (*it)->y));
	    break;
	  case HUMAN:
	    this->loadPlayer(it);
	    break;
	  case IA:
	    this->loadPlayer(it);
	    break;
	  default:
	    this->map_[(*it)->y][(*it)->x] = true;
	  }
	++it;
      }
  }

  void Map::buildGrid(void)
  {
    for (unsigned y = 0; y < this->height_; y++)
      {
    	std::vector<bool> tmp(this->width_, false);

    	if (y == 0 || y == (this->height_ - 1))
    	  tmp.assign(this->width_, true);
    	else
    	  {
    	    tmp.assign(this->width_, false);
    	    tmp[0] = true;
    	    tmp[this->width_ - 1] = true;
    	    for (unsigned int x = 1; x < this->width_; x++)
    	      {
    		if (y % 2 == 0 && x % 2 == 0)
    		  tmp[x] = true;
    	      }
    	  }
    	this->map_.push_back(tmp);
      }
  }

  void Map::loadRandomMap(int nb)
  {
    this->buildGrid();
    for (unsigned i = 0; i < this->height_ * this->width_ / 10; ++i)
      {
	int xtmp = 0;
	int ytmp = 0;
	do {
	  xtmp = (rand() % (this->width_ - 2)) + 1;
	  ytmp = (rand() % (this->height_ - 2)) + 1;
	} while (this->recoverObjectAt(xtmp, ytmp));
	this->addObject(new BreakableWall(this->gameEngine_, xtmp, ytmp));
      }
    for (unsigned i = 0; i < this->height_ * this->width_ / 50; ++i)
      {
	int xtmp = 0;
	int ytmp = 0;
	do {
	  xtmp = (rand() % (this->width_ - 2)) + 1;
	  ytmp = (rand() % (this->height_ - 2)) + 1;
	} while (this->recoverObjectAt(xtmp, ytmp)
		 || this->canEscape(xtmp, ytmp) == false);
	if ((int)i < nb)
	  this->addPlayer(new Human(this->gameEngine_, xtmp, ytmp));
	else
	  this->addPlayer(new Computer(this->gameEngine_, xtmp, ytmp));
      }
  }

  bool Map::canEscape(unsigned int x, unsigned int y)
  {
    for (unsigned int i = x + 1; !this->recoverObjectAt(i, y); ++i)
      if (!this->recoverObjectAt(i, y + 1) || !this->recoverObjectAt(i, y - 1))
	return true;
    for (unsigned int i = x - 1; !this->recoverObjectAt(i, y); --i)
      if (!this->recoverObjectAt(i, y + 1) || !this->recoverObjectAt(i, y - 1))
	return true;
    for (unsigned int i = y + 1; !this->recoverObjectAt(x, i); ++i)
      if (!this->recoverObjectAt(i + 1, y) || !this->recoverObjectAt(i - 1, y))
	return true;
    for (unsigned int i = y - 1; !this->recoverObjectAt(x, i) ; --i)
      if (!this->recoverObjectAt(i + 1, y) || !this->recoverObjectAt(i - 1, y))
	return true;
    return false;
  }

  void Map::buildShapes(void)
  {
    for (unsigned int y = 0; y < this->height_; y++)
      {
	if (y != 0 && y != (this->height_ - 1))
	  {
	    std::vector<bool> tmp(this->width_, false);
	    tmp[0] = true;
	    tmp[this->width_ - 1] = true;
	    this->map_.push_back(tmp);
	  }
	else
	  this->map_.push_back(std::vector<bool>(this->width_, true));
      }
  }

  bool Map::coorHasError(unsigned int x, unsigned int y) const
  {
    if (x < 1 || x >= (this->width_ - 1) ||
	y < 1 || y >= (this->height_ - 1))
      return true;
    if (this->recoverObjectAt(x, y))
      return true;
    return false;
  }

  void Map::loadPlayer(const std::list<bomberman::coords*>::const_iterator& it)
  {
    APlayer *p;

    if ((*it)->t == HUMAN)
      p = new Human(this->gameEngine_, (*it)->x, (*it)->y);
    else
      p = new Computer(this->gameEngine_, (*it)->x, (*it)->y);
    this->addPlayer(p);
    p->setBag((*it)->bag);
    p->setRange((*it)->bombRange);
    p->setSpeed((*it)->speed);
    p->setColor((*it)->color);
    p->incScore((*it)->score);
  }

  bool Map::loadMap(ABombxml *xm, unsigned int nb)
  {
    const std::list<bomberman::coords*>& li = xm->getList();
    std::list<bomberman::coords*>::const_iterator it = li.begin();
    unsigned int nbPlayers = 0;

    this->width_ = xm->getWidth();
    this->height_ = xm->getHeight();
    this->buildShapes();
    while (it != li.end())
      {
	if (this->coorHasError((*it)->x, (*it)->y))
	  throw Exception("Bad coordinates in LoadMap");

	if ((*it)->t == BREAKABLE_WALL)
	  this->addObject(new BreakableWall(this->gameEngine_, (*it)->x, (*it)->y));
	else if ((*it)->t == SPAWN)
	  {
	    if (nbPlayers++ < nb)
	      this->addPlayer(new Human(this->gameEngine_, (*it)->x, (*it)->y));
	    else
	      this->addPlayer(new Computer(this->gameEngine_, (*it)->x, (*it)->y));
	  }
	else
	  this->map_[(*it)->y][(*it)->x] = true;
	++it;
      }
    return true;
  }

  bool Map::isPermanentWall(unsigned int x, unsigned int y) const
  {
    return this->map_[y][x];
  }

  AElement *Map::recoverObjectAt(unsigned int x, unsigned int y) const
  {
    if (this->isPermanentWall(x, y))
      return this->pWall_;
    for (std::list<AElement *>::const_iterator it = this->o_.begin(); it != this->o_.end(); ++it)
      if ((*it)->getPosX() == x && (*it)->getPosY() == y && (*it)->isAlive())
	return (*it);
    return NULL;
  }

  bool Map::recoverPlayerAt(std::list<APlayer *>& tmp, unsigned int x, unsigned int y) const
  {
    for (std::list<APlayer *>::const_iterator it = this->p_.begin(); it != this->p_.end(); ++it)
      if ((*it)->getPosX() == x && (*it)->getPosY() == y && (*it)->isAlive())
	tmp.push_back((*it));
    return !tmp.empty();
  }

  void Map::addObject(AElement *o)
  {
    this->o_.push_back(o);
  }

  void Map::addPlayer(APlayer *p)
  {
    this->p_.push_back(p);
  }

  APlayer *Map::getPlayer(unsigned int id) const
  {
    unsigned int nb = (id > Human::getNbHumans() ? Human::getNbHumans() : id);
    std::list<APlayer *>::const_iterator it = this->p_.begin();

    while (it != this->p_.end() && nb > 0)
      {
	if ((*it)->getType() == HUMAN && nb-- == 1)
	  return (*it);
	++it;
      }
    return NULL;
  }

  APlayer *Map::getIA(unsigned int id) const
  {
    unsigned int nb = (id > Computer::getNbIAs() ? Computer::getNbIAs() : id);
    std::list<APlayer *>::const_iterator it = this->p_.begin();

    while (it != this->p_.end() && nb > 0)
      {
	if ((*it)->getType() == IA && nb-- == 1)
	  return (*it);
	++it;
      }
    return NULL;
  }

  void Map::updateObjects(void)
  {
    std::list<AElement *>::iterator it = this->o_.begin();
    std::list<AElement *>::iterator end = this->o_.end();

    while (it != end)
      {
	if ((*it)->isAlive())
	  {
	    (*it)->refresh();
	    ++it;
	  }
	else
	  {
	    delete (*it);
	    it = this->o_.erase(it);
	  }
      }
  }

  void Map::updatePlayers(void)
  {
    std::list<APlayer *>::iterator it = this->p_.begin();
    std::list<APlayer *>::iterator end = this->p_.end();

    this->nbIAsAlive_ = Computer::getNbIAs();
    this->nbPlayersAlive_ = Human::getNbHumans();

    while (it != end)
      {
	if ((*it)->isAlive())
	  (*it)->refresh();
	else
	  {
	    if ((*it)->getType() == IA)
	      this->nbIAsAlive_--;
	    else
	      this->nbPlayersAlive_--;
	  }
	++it;
      }
  }

  unsigned int Map::getWidth(void) const
  {
    return this->width_;
  }

  unsigned int Map::getHeight(void) const
  {
    return this->height_;
  }

  enum menu Map::isFinished(void) const
  {
    if (this->nbIAsAlive_ == 0 && this->nbPlayersAlive_ == 1)
      {
	if (Human::getNbHumans() == 1)
	  return PLAYER_1_WON;
	if (this->getPlayer(1)->isAlive())
	  return PLAYER_1_WON;
	return PLAYER_2_WON;
      }
    else if (this->nbPlayersAlive_ == 0)
      return IA_WON;
    return PLAYING;
  }
}
