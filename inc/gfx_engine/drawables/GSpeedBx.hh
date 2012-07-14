//
// GSpeedBx.hh for GSpeedBxerman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:50:18 2011 arnaud mesureur
//

#ifndef	GSPEEDBX_HH_
#define GSPEEDBX_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include <gdl/Image.hpp>

#include "DisplayLists.hh"
#include "IDrawable.hh"

namespace bomberman {
namespace gfx {

/**
 * The speed bonus.
 * @implements IDrawable
 */
class GSpeedBx : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the x position.
     * @param the y position.
     */
    GSpeedBx(float realX, float realY);

    /**
     * the draw implementation
     */
    void draw(void);

private:
    static gdl::Image texture_;
    DisplayLists& dlists_;
    float x_;
    float y_;
};

}}

#endif	// GSPEEDBX_HH_
