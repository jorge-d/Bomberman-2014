#include <cstdlib>
#include "GameEngine.hh"
#include "BreakableWall.hh"
#include "RangeBonus.hh"
#include "SpeedBonus.hh"
#include "BagBonus.hh"

namespace bomberman
{
  BreakableWall::BreakableWall(GameEngine *e, int x, int y) :
    AElement(e, x, y, BREAKABLE_WALL)
  {
  }

  BreakableWall::~BreakableWall(void)
  {
  }

  bool BreakableWall::refresh(void)
  {
    return this->isAlive();
  }

  void BreakableWall::kill(void)
  {
    int nb = rand() % 6;

    switch (nb)
      {
      case 1:
	this->gameEngine_->addObject(new RangeBonus(this->gameEngine_, this->getPosX(), this->getPosY()));
	break;
      case 2:
	this->gameEngine_->addObject(new SpeedBonus(this->gameEngine_, this->getPosX(), this->getPosY()));
	break;
      case 3:
	this->gameEngine_->addObject(new BagBonus(this->gameEngine_, this->getPosX(), this->getPosY()));
	break;
      }
    this->alive_ = false;
  }
}
