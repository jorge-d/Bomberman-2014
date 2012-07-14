//
// GWall.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 07:13:13 2011 arnaud mesureur
//

#ifndef	GWALL_HH_
#define	GWALL_HH_

#include <gdl/Image.hpp>

#include "IDrawable.hh"
#include "DisplayLists.hh"

namespace bomberman {
namespace gfx {

/**
 * A wall.
 * @implements IDrawable
 */
class GWall : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the x position
     * @param the y position
     */
    GWall(float realX, float realY);

    /**
     * The draw implementation.
     */
    void draw(void);

private:
    static gdl::Image texture_;
    DisplayLists& dlists_;
    float x_;
    float y_;
};

}}

#endif	// GWALL_HH_
