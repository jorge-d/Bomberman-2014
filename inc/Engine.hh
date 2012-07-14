//
// Engine.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 14:44:11 2011 arnaud mesureur
//

#ifndef	ENGINE_HH_
#define	ENGINE_HH_

#include <queue>

namespace bomberman {

class Game;
class GameEngine;
class GraphicsEngine;
class SoundEngine;

/**
 * Generic engine class.
 *
 * This class contains hard pointer to other engines.
 * It allows to access directly each engine faster and easier.
 * Whereas this requires knowing in advance the number of
 * modules to put in.
 *
 * @see Game
 * @see GameEngine
 * @see GraphicsEngine
 * @see SoundEngine
 */
class Engine
{
public:
    /**
     * Constructor.
     * @param game
     */
    Engine(Game*);
    /**
     * Destructor.
     */
    virtual ~Engine(void);

    /**
     * Attach game engine.
     * @param the game engine.
     */
    void attachEngine(GameEngine*);
    /**
     * Attach graphics engine.
     * @param the graphics engin.
     */
    void attachEngine(GraphicsEngine*);
    /**
     * Attach sound engine.
     * @param the sound engin.
     */
    void attachEngine(SoundEngine*);

    //////////////////////////////////////////
    /// Virtual member functions that need to
    /// be implemented by each engine.
    //////////////////////////////////////////
    virtual void initialize(void) = 0;
    virtual void update(void) = 0;
    virtual void unload(void) = 0;

protected:
    Game* parent_;
    GameEngine* gameEngine_;
    GraphicsEngine* graphicsEngine_;
    SoundEngine* soundEngine_;

private:
    Engine(Engine const&);
    Engine& operator=(Engine const&);
};

}

#endif	// ENGINE_HH_
