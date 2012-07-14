#include "AElement.hh"

namespace bomberman
{
  AElement::AElement(GameEngine *e, unsigned int x, unsigned int y, elemType t, Direction d) :
    gameEngine_(e), posX_(x), posY_(y), type_(t), dir_(d), alive_(true)

  {
  }

  AElement::~AElement(void)
  {
  }

  unsigned int AElement::getPosX(void) const
  {
    return this->posX_;
  }

  unsigned int AElement::getPosY(void) const
  {
    return this->posY_;
  }

  elemType AElement::getType(void) const
  {
    return this->type_;
  }

  bool AElement::isAlive(void) const
  {
    return this->alive_;
  }

  void AElement::kill(void)
  {
    this->alive_ = false;
  }

  Direction AElement::getDirection(void) const
  {
    return this->dir_;
  }
}
