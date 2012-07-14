//
// GFlame.hh for GFlameerman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:50:18 2011 arnaud mesureur
//

#ifndef	GFLAME_HH_
#define GFLAME_HH_

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
class GFlame : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the x position.
     * @param the y position.
     */
    GFlame(float realX, float realY);

    /**
     * The draw implementation
     */
    void draw(void);

private:
    static gdl::Image texture_;
    DisplayLists& dlists_;
    float x_;
    float y_;
};

}}

#endif	// GFLAME_HH_
