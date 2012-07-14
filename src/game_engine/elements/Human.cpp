#include "Human.hh"
#include "GameEngine.hh"
#include "Map.hh"
#include "Bomb.hh"
#include "Exception.hh"
#include <cstdlib>

namespace bomberman
{
  unsigned int Human::nbPlayers = 0;

  Human::Human(GameEngine *e, int x, int y) :
    APlayer(e, x, y, HUMAN)
  {
    if (Human::nbPlayers == 0)
      {
          this->keyUp_ = gdl::Keys::Up;
          this->keyDown_ = gdl::Keys::Down;
          this->keyLeft_ = gdl::Keys::Left;
          this->keyRight_ = gdl::Keys::Right;
          this->setBomb_ = gdl::Keys::RShift;
          Human::nbPlayers++;
      }
    else
      {
          this->keyUp_ = gdl::Keys::W;
          this->keyDown_ = gdl::Keys::S;
          this->keyLeft_ = gdl::Keys::A;
          this->keyRight_ = gdl::Keys::D;
          this->setBomb_ = gdl::Keys::LShift;
          if (Human::nbPlayers++ >= 2)
	    throw Exception("Too many humans were generated");
      }
    this->actionsP_[LEFT] = &Human::moveLeft;
    this->actionsP_[RIGHT] = &Human::moveRight;
    this->actionsP_[UP] = &Human::moveUp;
    this->actionsP_[DOWN] = &Human::moveDown;
  }

  Human::~Human(void)
  {
    Human::nbPlayers--;
  }

  void Human::moveLeft(void)
  {
    int x = this->getPosX() - 1;
    int y = this->getPosY();
    this->move(x, y, LEFT);
  }

  void Human::moveRight(void)
  {
    int x = this->getPosX() + 1;
    int y = this->getPosY();
    this->move(x, y, RIGHT);
  }

  void Human::moveUp(void)
  {
    int x = this->getPosX();
    int y = this->getPosY() - 1;
    this->move(x, y, UP);
  }

  void Human::moveDown(void)
  {
    int x = this->getPosX();
    int y = this->getPosY() + 1;
    this->move(x, y, DOWN);
  }

  Direction Human::getMoveKey(void) const
  {
    if (this->gameEngine_->isKeyDown(this->keyUp_))
      return UP;
    if (this->gameEngine_->isKeyDown(this->keyDown_))
      return DOWN;
    if (this->gameEngine_->isKeyDown(this->keyLeft_))
      return LEFT;
    if (this->gameEngine_->isKeyDown(this->keyRight_))
      return RIGHT;
    return NONE;
  }

  bool Human::refresh(void)
  {
    Direction t;

    if (this->gameEngine_->isKeyDown(this->setBomb_))
      this->setBomb();
    if (this->gameEngine_->getElapsedTime() - this->timer_ > this->speed_)
      if ((t = this->getMoveKey()) != NONE)
	(this->*(this->actionsP_[t]))();
    return this->isAlive();
  }

  unsigned int Human::getNbHumans(void)
  {
    return Human::nbPlayers;
  }
}
