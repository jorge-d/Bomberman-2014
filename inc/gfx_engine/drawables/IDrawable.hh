//
// IDrawable.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Fri May 20 19:21:05 2011 arnaud mesureur
//

#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_

namespace bomberman {
namespace gfx {

/**
 * Drawable interface.
 * Force to implement a draw member
 * function.
 */
class IDrawable
{
public:
    virtual ~IDrawable(void) {}

    /**
     * Draw the object.
     */
    virtual void draw(void) = 0;
};

}}

#endif	// IDRAWABLE_H_
