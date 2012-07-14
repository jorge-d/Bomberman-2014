//
// Game.hh for Bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Tue May 10 20:58:52 2011 arnaud mesureur
//

#ifndef	GAME_HH_
#define	GAME_HH_

#include "gdl/Game.hpp"
#include "GraphicsEngine.hh"
#include "SoundEngine.hh"
#include "GameEngine.hh"

namespace bomberman {

/**
 * The Game class.
 *
 * Instanciation of this class start the game.
 * This class contains and instantiate all
 * the engines of the game.
 *
 * This class can only be instantiate once at a time.
 *
 * @see Engine
 * @see GameEngine
 * @see GraphicsEngine
 * @see SoundEngine
 */
class Game : public gdl::Game
{
//////////////////////////////////////////
/// Public members
//////////////////////////////////////////
public:
    /**
     * Provide an easy access to the gameClock;
     */
    static gdl::GameClock* getGameClock(void);

public:
    Game(void);
    ~Game(void);

    void initialize(void);
    void update(void);
    void draw(void);
    void unload(void);

    gdl::Input& getInput(void);
    gdl::GameClock& getClock(void);

//////////////////////////////////////////
/// Private members
//////////////////////////////////////////
private:
    static gdl::GameClock* gameClockPtr_;
    static int nbInstance_;

private:
    GameEngine* gameEngine_;
    GraphicsEngine* graphicsEngine_;
    SoundEngine* soundEngine_;

private:
    void die(const char*) const;

//////////////////////////////////////////
/// Not implemented
//////////////////////////////////////////
private:
    Game(Game const&);
    Game& operator=(Game const&);
};
}

#endif	// GAME_HH_
