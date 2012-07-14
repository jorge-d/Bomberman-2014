#include "GameEngine.hh"
#include "Flame.hh"
#include "SoundEngine.hh"

namespace bomberman
{
  Flame::Flame(GameEngine *e, APlayer &p, int x, int y, int r, Direction d) :
    AElement(e, x, y, FLAME, d), p_(p), range_(r), nextX_(x), nextY_(y), spread_(true)
  {
    AElement *elem = NULL;
    std::list<APlayer *> pls;
    unsigned int score = 0;

    this->timer_ = e->getElapsedTime();
    if (this->gameEngine_->recoverPlayerAt(pls, x, y))
      for (std::list<APlayer *>::iterator it = pls.begin(); it != pls.end(); ++it)
	score += Constants::ScoreKillingPlayer, (*it)->kill();

    if (r == 0 || d == NONE)
      this->spread_ = false;
    switch (this->dir_)
      {
      case UP:
	this->nextY_--;
	break;
      case DOWN:
	this->nextY_++;
	break;
      case LEFT:
	this->nextX_--;
	break;
      case RIGHT:
	this->nextX_++;
	break;
      default:
	p.incScore(score);
	return;
      }
    if ((elem = this->gameEngine_->recoverObjectAt(x, y)))
      {
	elem->kill();
	if (elem->getType() == BREAKABLE_WALL)
	  {
	    this->gameEngine_->playSound(BREAK_BOX);
	    score += Constants::ScoreDestroyingBox;
	  }
	if (elem->getType() != FLAME)
	  this->spread_ = false;
      }
    if (this->gameEngine_->getMap()->isPermanentWall(this->nextX_, this->nextY_))
      this->spread_ = false;
    p.incScore(score);
  }

  Flame::~Flame(void)
  {
  }

  bool Flame::refresh(void)
  {
    if (!this->spread_)
      {
	float sub = (Constants::DissipateFlameMultiplier * static_cast<float>(this->range_))
	  + Constants::DefaultTimeDissipateFlame;
	if (this->gameEngine_->getElapsedTime() - this->timer_ > sub)
	  this->kill();
      }
    else if (this->gameEngine_->getElapsedTime() - this->timer_ > Constants::TimeBeforeFlameSpreading)
      {
	this->gameEngine_->addObject(new Flame(this->gameEngine_, this->p_, this->nextX_,
					       this->nextY_, this->range_ - 1, this->dir_));
	this->spread_ = false;
      }
    return this->isAlive();
  }
}
