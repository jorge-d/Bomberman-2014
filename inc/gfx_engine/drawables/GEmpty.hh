//
// GEmpty.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:50:18 2011 arnaud mesureur
//

#ifndef	GEMPTY_HH_
#define GEMPTY_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include <Image.hpp>

#include "DisplayLists.hh"
#include "IDrawable.hh"

namespace bomberman {
namespace gfx {

/**
 * The flame.
 * @implements IDrawable
 */
class GEmpty : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the x position.
     * @param the y position.
     */
    GEmpty(float realX, float realY);

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

#endif	// GEMPTY_HH_
