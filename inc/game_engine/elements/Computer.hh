#ifndef __COMPUTER_HH__
# define __COMPUTER_HH__

# include "APlayer.hh"
# include "LuaBind.hh"
# include <map>

# define NONEG(nb) ((nb) < 0) ? (0) : (nb)

namespace bomberman
{
  class Computer : public APlayer
  {
  private:
    lua::LuaBind lua_;
    GameEngine *game_engine_;
    std::map<Direction, void (Computer::*)(void)> actionsP_;
    bool is_good_;

    void moveLeft(void);
    void moveRight(void);
    void moveUp(void);
    void moveDown(void);
    static unsigned int nbIAs;

    std::string* mapToStringTab(void);
  public:
    Computer(GameEngine *e, int x, int y);
    ~Computer(void);
    bool refresh(void);

    static unsigned int getNbIAs(void);
  };
}
#endif
