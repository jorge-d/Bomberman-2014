//
// DrawableFactory.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 09:31:11 2011 arnaud mesureur
//

#ifndef DRAWABLE_FACTORY_HH_
#define DRAWABLE_FACTORY_HH_

#include <map>

#include "AElement.hh"
#include "IDrawable.hh"

namespace bomberman {
namespace gfx {

/**
 * A Drawable object factory.
 * @see IDrawable
 */
class DrawableFactory
{
public:
    /**
     * Constructor.
     */
    DrawableFactory(void);

    /**
     * Build a drawable object.
     * @param the element type.
     * @param the element.
     * @param the x position.
     * @param the y position.
     */
    IDrawable* build(enum elemType, AElement*, float x, float y);

private:
    typedef IDrawable* (DrawableFactory::*builder)(AElement*, float x, float y);
    std::map<enum elemType, builder> builders_;

private:
    IDrawable* buildWall(AElement*, float x, float y);
    IDrawable* buildBox(AElement*, float x, float y);
    IDrawable* buildPlayer(AElement*, float x, float y);
    IDrawable* buildBomb(AElement*, float x, float y);
    IDrawable* buildFlame(AElement*, float x, float y);
    IDrawable* buildRangeBonus(AElement*, float x, float y);
    IDrawable* buildBagBonus(AElement*, float x, float y);
    IDrawable* buildSpeedBonus(AElement*, float x, float y);
    IDrawable* buildEmpty(AElement*, float x, float y);
};

}}

#endif	// DRAWABLE_FACTORY_HH_

