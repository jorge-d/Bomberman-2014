//
// GBagBx.cpp for GBomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:51:53 2011 arnaud mesureur
//


#include <gdl/Image.hpp>

#include "LoadHelper.hpp"
#include "BindHelper.hh"
#include "DisplayLists.hh"
#include "GBagBx.hh"

namespace bomberman {
namespace gfx {

gdl::Image GBagBx::texture_ = loadHelper<gdl::Image>("./assets/textures/bag.png");

GBagBx::GBagBx(float realX, float realY)
    : dlists_(DisplayLists::getInstance()),
      x_(realX), y_(realY)
{
}

void GBagBx::draw(void)
{
    BindHelper::bind(this->texture_, BAG);
    glPushMatrix();
    glTranslatef(this->x_, 0, this->y_);
    this->dlists_[TCUBE];
    glPopMatrix();
}

}}
