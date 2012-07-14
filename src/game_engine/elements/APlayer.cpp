#include <Color.hpp>
#include "APlayer.hh"
#include "GameEngine.hh"
#include "Map.hh"
#include "Bomb.hh"
#include "Constants.hh"
#include "Human.hh"
#include "Computer.hh"

namespace bomberman
{
  APlayer::APlayer(GameEngine *e, unsigned int x, unsigned int y, elemType t) :
    AElement(e, x, y, t), bombRange_(Constants::DefaultBombRange),
    speed_(Constants::DefaultSpeed), color_(gdl::Color(42,42,42,42)),
    score_(0), bag_(Constants::DefaultBag), bombSetNb_(0)
  {
    this->timer_ = e->getElapsedTime();
    this->idPlayer_ = Human::getNbHumans() + Computer::getNbIAs();
    this->generateColor();
  }

  APlayer::~APlayer(void)
  {
  }

  void APlayer::generateColor(void)
  {
    this->color_ = gdl::Color(rand() % 256, rand() % 256, rand() % 256);
  }

  unsigned int APlayer::getRange(void) const
  {
    return this->bombRange_;
  }

  int APlayer::getID(void) const
  {
    return this->idPlayer_;
  }

  float APlayer::getSpeed(void) const
  {
    return this->speed_;
  }

  const gdl::Color &APlayer::getColor(void) const
  {
    return this->color_;
  }

  unsigned int APlayer::getScore(void) const
  {
    return this->score_;
  }

  unsigned int APlayer::getBag(void) const
  {
    return this->bag_;
  }

  void APlayer::incScore(unsigned int s)
  {
    this->score_ += s;
  }

  void APlayer::incRange(void)
  {
    if (this->bombRange_ < Constants::MaxBombRange)
      this->bombRange_++;
  }

  void APlayer::incBag(void)
  {
    if (this->bag_ < Constants::MaxBag)
      this->bag_++;
  }

  void APlayer::setBag(unsigned int b)
  {
    this->bag_ = (b < Constants::MaxBag ? b : Constants::MaxBag);
  }

  void APlayer::setRange(unsigned int b)
  {
    this->bombRange_ = (b < Constants::MaxBombRange ? b : Constants::MaxBombRange);
  }

  void APlayer::setSpeed(float s)
  {
    this->speed_ = (s < Constants::MaxSpeed ? Constants::MaxSpeed : s);
  }

  void APlayer::setColor(const gdl::Color& c)
  {
    this->color_ = c;
  }

  unsigned int APlayer::getBombSetNb(void) const
  {
    return this->bombSetNb_;
  }

  void APlayer::decBombSetNb(void)
  {
    this->bombSetNb_--;
  }

  void APlayer::incSpeed(void)
  {
    if (this->speed_ > Constants::MaxSpeed)
      this->speed_ -= 0.01f;
  }

  bool APlayer::isMoving(void) const
  {
    if ((this->gameEngine_->getElapsedTime() - this->timer_) < this->speed_)
      return true;
    return false;
  }

  float APlayer::getRealPosX(void) const
  {
    float x = static_cast<float>(this->posX_);
    float ratio = (this->gameEngine_->getElapsedTime() - this->timer_) / this->speed_;

    if (ratio >= 1)
      return x;
    ratio = 1 - ratio;
    if (this->dir_ == LEFT)
      return x += ratio;
    else if (this->dir_ == RIGHT)
      return x -= ratio;
    return x;
  }

  float APlayer::getRealPosY(void) const
  {
    float y = static_cast<float>(this->posY_);
    float ratio = (this->gameEngine_->getElapsedTime() - this->timer_) / this->speed_;

    if (ratio >= 1)
      return y;
    ratio = 1 - ratio;
    if (this->dir_ == DOWN)
      return y -= ratio;
    else if (this->dir_ == UP)
      return y += ratio;
    return y;
  }

  bool APlayer::setBomb(void)
  {
    if (this->bombSetNb_ >= this->bag_ || this->gameEngine_->recoverObjectAt(this->getPosX(), this->getPosY()))
      return false;
    this->gameEngine_->addObject(new Bomb(this->gameEngine_, this->getPosX(), this->getPosY(), this->bombRange_, *this));
    this->bombSetNb_++;
    return true;
  }

  void APlayer::move(int x, int y, Direction d)
  {
    AElement *tmp = this->gameEngine_->recoverObjectAt(x, y);

    this->dir_  = d;
    if (tmp)
      {
	switch (tmp->getType())
	  {
	  case RANGE_BONUS:
	    this->incRange();
	    break;
	  case BAG_BONUS:
	    this->incBag();
	    break;
	  case SPEED_BONUS:
	    this->incSpeed();
	    break;
	  case FLAME:
	    this->kill();
	    return;
	  default:
	    return;
	  }
	tmp->kill();
	this->gameEngine_->playSound(POWER_UP);
	this->incScore(Constants::ScoreGettingBonus);
      }
    this->posX_ = x;
    this->posY_ = y;
    this->timer_ = this->gameEngine_->getElapsedTime();
  }
}
