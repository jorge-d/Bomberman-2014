#ifndef __HUMAN_HH__
# define __HUMAN_HH__

#include "APlayer.hh"
#include <map>
#include "Game.hh"

namespace bomberman
{
  class Human : public APlayer
  {
  private:
    std::map<Direction, void (Human::*)(void)> actionsP_;
    gdl::Keys::Key keyUp_;
    gdl::Keys::Key keyDown_;
    gdl::Keys::Key keyLeft_;
    gdl::Keys::Key keyRight_;
    gdl::Keys::Key setBomb_;

    static unsigned int nbPlayers;

  private:
    Direction getMoveKey(void) const;
    void moveLeft(void);
    void moveRight(void);
    void moveUp(void);
    void moveDown(void);

  public:
    Human(GameEngine *e, int x, int y);
    ~Human(void);
    bool refresh(void);

    static unsigned int getNbHumans(void);
  };
}
#endif
