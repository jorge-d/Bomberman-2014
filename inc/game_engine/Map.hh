#ifndef __MAP_HH__
# define __MAP_HH__

#include <vector>
#include <list>
#include <string>
#include "AElement.hh"
#include "APlayer.hh"
#include "GameEngine.hh"
#include "PermanentWall.hh"
#include "ABombxml.hh"
#include "Constants.hh"

namespace bomberman
{
  class GameEngine;
  class AElement;
  class APlayer;

  class Map
  {
  private:
    GameEngine *gameEngine_;
    std::vector<std::vector<bool> > map_;
    std::list<AElement *> o_;
    std::list<APlayer *> p_;
    unsigned int width_;
    unsigned int height_;
    PermanentWall *pWall_;
    unsigned int nbIAsAlive_;
    unsigned int nbPlayersAlive_;

  public:
    Map(GameEngine *, ABombxml *, unsigned int);
    Map(GameEngine *, ABombxml *);
    ~Map(void);

  private:
    void loadRandomMap(int);
    bool loadMap(ABombxml *, unsigned int);
    void loadSave(ABombxml *);
    bool canEscape(unsigned int, unsigned int);
    void buildShapes(void);
    bool coorHasError(unsigned int, unsigned int) const;
    void loadPlayer(const std::list<bomberman::coords*>::const_iterator&);
    void buildGrid(void);

  public:
    bool isPermanentWall(unsigned int, unsigned int) const;
    AElement *recoverObjectAt(unsigned int, unsigned int) const;
    bool recoverPlayerAt(std::list<APlayer *>&, unsigned int, unsigned int) const;

    unsigned int getWidth(void) const;
    unsigned int getHeight(void) const;
    enum menu isFinished(void) const;
    void addObject(AElement *);
    void addPlayer(APlayer *);
    void updateObjects(void);
    void updatePlayers(void);
    APlayer *getPlayer(unsigned int) const;
    APlayer *getIA(unsigned int) const;
  };
}

#endif
