//
// GBox.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:50:18 2011 arnaud mesureur
//

#ifndef	GBOX_HH_
#define GBOX_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include <Image.hpp>

#include "DisplayLists.hh"
#include "IDrawable.hh"

namespace bomberman {
namespace gfx {

/**
 * The box.
 * @implements IDrawable
 */
class GBox : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the x position.
     * @param the y position.
     */
    GBox(float realX, float realY);

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

#endif	// GBOX_HH_
