#include "GameEngine.hh"
#include "Bomb.hh"
#include "Flame.hh"
#include "SoundEngine.hh"

namespace bomberman
{
  Bomb::Bomb(GameEngine *e, int x, int y, int r, APlayer &p) :
    AElement(e, x, y, BOMB), range_(r), p_(p)
  {
    this->timer_ = e->getElapsedTime();
  }

  Bomb::~Bomb(void)
  {
  }

  bool Bomb::refresh(void)
  {
    if ((this->gameEngine_->getElapsedTime() - this->timer_) > Constants::TimeBeforeExplosion)
      this->kill();
    return this->isAlive();
  }

  void Bomb::createFlame(unsigned int x, unsigned int y, unsigned int r, Direction d)
  {
    if (!this->gameEngine_->getMap()->isPermanentWall(x, y))
      this->gameEngine_->addObject(new Flame(this->gameEngine_, this->p_, x, y, r, d));
  }

  void Bomb::kill(void)
  {
    this->p_.decBombSetNb();
    this->gameEngine_->playSound(EXPLOSION);
    this->alive_ = false;
    this->createFlame(this->getPosX(), this->getPosY(), this->range_, NONE);
    this->createFlame(this->getPosX(), this->getPosY() - 1, this->range_ - 1, UP);
    this->createFlame(this->getPosX(), this->getPosY() + 1, this->range_ - 1, DOWN);
    this->createFlame(this->getPosX() - 1, this->getPosY(), this->range_ - 1, LEFT);
    this->createFlame(this->getPosX() + 1, this->getPosY(), this->range_ - 1, RIGHT);
  }
}
