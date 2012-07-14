#ifndef __A_PLAYER_HH__
# define __A_PLAYER_HH__

#include <Color.hpp>
#include "AElement.hh"

namespace bomberman
{

  union color
  {
    int color;
    char c[4];
  };

  class APlayer : public AElement
  {
  protected:
    unsigned int bombRange_;
    float speed_;
    gdl::Color color_;
    unsigned int  score_;
    unsigned int bag_;
    unsigned int bombSetNb_;
    float timer_;
    int idPlayer_;

  private:
    void generateColor(void);

  public:
    APlayer(GameEngine *, unsigned int, unsigned int, elemType);

    virtual ~APlayer(void);
    virtual bool refresh(void) = 0;

    float getRealPosX(void) const;
    float getRealPosY(void) const;

    int getID(void) const;
    unsigned int getRange(void) const;
    float getSpeed(void) const;
    const gdl::Color & getColor(void) const;
    unsigned int getScore(void) const;
    unsigned int getBag(void) const;

    unsigned int getBombSetNb(void) const;
    void decBombSetNb(void);

    void incScore(unsigned int);
    void setBag(unsigned int);
    void setRange(unsigned int);
    void setSpeed(float);
    void setColor(const gdl::Color&);

    bool isMoving(void) const;

  protected:
    bool setBomb(void);
    void incRange(void);
    void incSpeed(void);
    void incBag(void);
    void move(int, int, Direction = NONE);
  };
}
#endif
