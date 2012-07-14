//
// DrawableFactory.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 09:44:54 2011 arnaud mesureur
//

#include <cstdlib>
#include <iostream>

#include "DrawableFactory.hh"

#include "IDrawable.hh"
#include "GBomb.hh"
#include "GWall.hh"
#include "GBox.hh"
#include "GPlayer.hh"
#include "GEmpty.hh"
#include "GFlame.hh"
#include "GBagBx.hh"
#include "GRangeBx.hh"
#include "GSpeedBx.hh"

namespace bomberman {
namespace gfx {

//////////////////////////////////////////
/// Constructor
//////////////////////////////////////////

DrawableFactory::DrawableFactory(void)
{
    this->builders_[PERMANENT_WALL] = &DrawableFactory::buildWall;
    this->builders_[BREAKABLE_WALL] = &DrawableFactory::buildBox;
    this->builders_[HUMAN] = &DrawableFactory::buildPlayer;
    this->builders_[IA] = &DrawableFactory::buildPlayer;
    this->builders_[BOMB] = &DrawableFactory::buildBomb;
    this->builders_[FLAME] = &DrawableFactory::buildFlame;
    this->builders_[BAG_BONUS] = &DrawableFactory::buildBagBonus;
    this->builders_[RANGE_BONUS] = &DrawableFactory::buildRangeBonus;
    this->builders_[SPEED_BONUS] = &DrawableFactory::buildSpeedBonus;
}

//////////////////////////////////////////
/// Public member functions
//////////////////////////////////////////

IDrawable* DrawableFactory::build(enum elemType type, AElement* e, float x, float y)
{
    std::map<enum elemType, DrawableFactory::builder>::iterator it = this->builders_.find(type);
    if (it != this->builders_.end())
    {
        builder b = (*it).second;
        return (this->*b)(e, x, y);
    }
    return NULL;
}

//////////////////////////////////////////
/// Private member functions
//////////////////////////////////////////

IDrawable* DrawableFactory::buildWall(AElement* e, float x, float y)
{
    (void)e;
    return new gfx::GWall(x, y);
}

IDrawable* DrawableFactory::buildBox(AElement* e, float x, float y)
{
    (void)e;
    return new gfx::GBox(x, y);
}

IDrawable* DrawableFactory::buildPlayer(AElement* e, float x, float y)
{
    return new gfx::GPlayer(e, x, y);
}

IDrawable* DrawableFactory::buildBomb(AElement* e, float x, float y)
{
    return new gfx::GBomb(e, x, y);
}

IDrawable* DrawableFactory::buildFlame(AElement* e, float x, float y)
{
    (void) e;
    return new gfx::GFlame(x, y);
}

IDrawable* DrawableFactory::buildRangeBonus(AElement* e, float x, float y)
{
    (void) e;
    return new gfx::GRangeBx(x, y);
}

IDrawable* DrawableFactory::buildBagBonus(AElement* e, float x, float y)
{
    (void) e;
    return new gfx::GBagBx(x, y);
}

IDrawable* DrawableFactory::buildSpeedBonus(AElement* e, float x, float y)
{
    (void) e;
    return new gfx::GSpeedBx(x, y);
}

IDrawable* DrawableFactory::buildEmpty(AElement* e, float x, float y)
{
    (void) e;
    return new gfx::GEmpty(x, y);
}

}}
