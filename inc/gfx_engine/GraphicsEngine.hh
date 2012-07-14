//
// Graphicsengine.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 17:11:41 2011 arnaud mesureur
//

#ifndef	GRAPHICS_ENGINE_HH_
#define	GRAPHICS_ENGINE_HH_

#include "gdl/Window.hpp"

#include "Engine.hh"
#include "Menu.hh"
#include "Camera.hh"
#include "ScreenBoard.hh"
#include "DisplayLists.hh"

namespace bomberman {

/**
 * The graphics engine.
 * @see Engine
 */
class GraphicsEngine : public Engine
{
public:
    /**
     * Constructor.
     * @param the game.
     */
    GraphicsEngine(Game*);
    /**
     * Destructor.
     */
    ~GraphicsEngine(void);

public:
    /**
     * Initialize graphic engine.
     * It initializes and creates the window and
     * the openGL display lists.
     */
    void initialize(void);

    /**
     * Update the graphic engine.
     * It updates the menus or the game depending on
     * the game engine status. The screenboards are updates
     * depending on the number of players (2 human max).
     */
    void update(void);

    /**
     * Draw the menus or the game scene, depending on the
     * game engine status. The screenboards are drawn depending
     * on the number of players (2 human max).
     */
    void draw(void);

    /**
     * Unload the graphic engine datas.
     */
    void unload(void);

private:
    gdl::Window window_;
    gfx::DisplayLists& dlists_;
    gfx::ScreenBoard boardP1_;
    gfx::ScreenBoard boardP2_;
    gfx::Menu menu_;
    bool multiplayer_;
    bool reload_;

private:
    void reload(void);

//////////////////////////////////////////
/// Not Implemented
//////////////////////////////////////////
private:
    GraphicsEngine(GraphicsEngine const&);
    GraphicsEngine& operator=(Engine const&);
};

//////////////////////////////////////////
/// full screen mode flag
//////////////////////////////////////////
extern bool fullscreen;

//////////////////////////////////////////
/// The window size default parameters
//////////////////////////////////////////
const unsigned int defaultWinW = 1024;
const unsigned int defaultWinH = 768;

}

#endif	// GRAPHICS_ENGINE_HH_
