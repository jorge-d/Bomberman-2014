//
// ScreenBoard.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 06:51:07 2011 arnaud mesureur
//

#ifndef	SCREEN_BOARD_HH_
#define	SCREEN_BOARD_HH_

#include <list>

#include "gdl/Image.hpp"
#include "gdl/Window.hpp"

#include "DisplayLists.hh"
#include "Camera.hh"
#include "APlayer.hh"
#include "Square.hh"

namespace bomberman {

class Map;

namespace gfx {

/**
 * The screenboard.
 * Each human player is linked with a screenboard by a single id.
 * The screenboard describes the map around this player.
 * @see Square.
 * @see Camera.
 * @see Map.
 */
class ScreenBoard
{
//////////////////////////////////////////
/// Public members
//////////////////////////////////////////
public:
    /**
     * Constructor.
     */
    ScreenBoard(void);
    /**
     * Destructor.
     */
    ~ScreenBoard(void);

public:
    /**
     * Initialize the screenboard with the game engine map datas.
     * The party must be already launched and the map and the players
     * must be sets.
     * @param the map.
     */
    void initialize(Map* map);
    /**
     * Update the screenboard datas.
     * Each square is reload and the player position is update.
     */
    void update(void);
    /**
     * Draws each square of the screenboard
     * and unload it.
     */
    void draw(void);

//////////////////////////////////////////
/// Private members
//////////////////////////////////////////
private:
    static const int radius_;

private:
    static int idGen_;
    int id_;
    Camera camera_;

    bool isInitialized_;
    Map* map_;
    APlayer* player_;
    std::list<Square*> board_;

    DisplayLists& dlists_;
    gdl::Image background_;

private:
    void drawBackground(void);
    void drawSplitLine(void) const;
    void drawScore(void) const;

private:
    ScreenBoard(ScreenBoard const&);
    ScreenBoard& operator=(ScreenBoard const&);
};

}}

#endif	// SCREEN_BOARD_HH_
