//
// GameEngine.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 16:59:53 2011 arnaud mesureur
//

#ifndef	GAME_ENGINE_HH_
#define	GAME_ENGINE_HH_

#include <list>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "Clock.hpp"
#include "Engine.hh"
#include "APlayer.hh"
#include "Map.hh"
#include "Input.hpp"
#include "ABombxml.hh"
#include "Constants.hh"
#include "Scores.hh"
#include "SoundEngine.hh"
namespace bomberman
{
  class Map;
  /**
   * The game core engine.
   * @see Engine
   */
  class GameEngine : public Engine
  {
  private:
    enum menu menuStatus_;
    std::map<enum menu, void (GameEngine::*)(void)> mptr_;
    Map *map_;
    gdl::Clock clock_;
    unsigned int cursorIndex_;
    std::vector<std::string> mainmenu_;
    std::vector<std::string> pausemenu_;
    std::vector<ABombxml *> maplist_;
    std::vector<ABombxml *> saveslist_;
    float timer_;
    Scores score_;
    bool reloadSave_;
    std::string nickname_;

  public:
    GameEngine(Game*);
    ~GameEngine(void);

  public:
    enum menu getMenuStatus(void) const;

    Map *getMap(void) const;

    const std::vector<ABombxml *> getMapList(void) const;
    const std::list<score *>& getScoreList(void);
    const std::vector<ABombxml *> getSavesList(void) const;
    const std::vector<std::string> getPauseMenuString(void) const;
    const std::vector<std::string> getMainMenuString(void) const;
    const std::string& getNickname(void) const;

    unsigned int getCursor(void) const;
    float getElapsedTime(void) const;

    AElement *recoverObjectAt(unsigned int, unsigned int) const;
    bool recoverPlayerAt(std::list<APlayer *>&, unsigned int, unsigned int) const;
    bool isKeyDown(gdl::Keys::Key);

    void playSound(playable_id);
    /**
     * Those functions are called into the Game Loop
     * @see Game class
     */
    void initialize(void);
    void update(void);
    void unload(void);

    void addObject(AElement *) const;
    void addPlayer(APlayer *) const;

  private:
    void loadFromFile(bool = false);
    void deleteSaves(void);
    void deleteMaps(void);
    void loadMaps(void);
    void loadSaves(void);
    void loadMenus(void);

    void incCursor(void);
    void decCursor(void);
    bool validateSelection(void);
    void startPlaying(bool = false);
    void returnMainMenu(void);
    bool navigateNickName(void);
    void changeLetter(bool);

    void handleIntroduction(void);
    void handleMainMenu(void);
    void handleNewGame(void);
    void handleLoadGame(void);
    void handlePausedGame(void);
    void handleEndOfGame(void);
    void handleLoosedGame(void);
    void handleDisplayScore(void);
    void handlePlaying(void);

    GameEngine(const GameEngine&);
    GameEngine& operator=(const Engine&);
  };

}

#endif	// GAME_ENGINE_HH_
