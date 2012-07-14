//
// Square.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 03:30:22 2011 arnaud mesureur
//

#ifndef	SQUARE_HH_
#define	SQUARE_HH_

#include <map>
#include <list>

#include "IDrawable.hh"
#include "GPlayer.hh"
#include "DrawableFactory.hh"

namespace bomberman {

class Map;
class APlayer;
class AElement;

namespace gfx {

/**
 * The Square class.
 * A square of the screen board.
 *
 * @see ScreenBoard
 */
class Square
{
//////////////////////////////////////////
/// Public member.
//////////////////////////////////////////
public:
    static const unsigned size;

public:
    /**
     * Constructor.
     * @param the screenboard/player parent id.
     * @param the x position on map.
     * @param the y position on map.
     */
    Square(int parentId, Map* map, unsigned int posX, unsigned int posY);
    /**
     * Destructor.
     */
    ~Square(void);

    /**
     * Draw the square.
     */
    void draw(void);

    /**
     * Unload the stock of GPlayers
     */
    static void unload(void);

//////////////////////////////////////////
/// Private member.
//////////////////////////////////////////

private:
    /// optimization to avoid models to be reloaded.
    static std::map<int, GPlayer*> stock_;

private:
    int parentId_;
    Map* map_;
    unsigned int mapX_;
    unsigned int mapY_;
    float realX_;
    float realY_;

    DrawableFactory factory_;
    std::list<IDrawable*> gfxContent_;
    std::list<GPlayer*> gfxPlayers_;
    std::list<APlayer*> players_;
    AElement* object_;

private:
    void load(void);
};

}}

#endif	// SQUARE_HH_
