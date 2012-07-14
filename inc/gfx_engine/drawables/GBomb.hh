//
// GBomb.hh for GBomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:50:18 2011 arnaud mesureur
//

#ifndef	GBOMB_HH_
#define GBOMB_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include <Image.hpp>
#include <Model.hpp>

#include "DisplayLists.hh"
#include "AElement.hh"
#include "IDrawable.hh"

namespace bomberman {
namespace gfx {

/**
 * The bomb.
 * @implements IDrawable
 */
class GBomb : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the element.
     * @param the x position.
     * @param the y position.
     */
    GBomb(AElement* e, float realX, float realY);

    /**
     * the draw implementation
     */
    void draw(void);

private:
    static gdl::Image texture_;
    static gdl::Model model_;
    DisplayLists& dlists_;
    float x_;
    float y_;
};

}}

#endif	// GBOMB_HH_
