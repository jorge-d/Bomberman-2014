//
// GRangeBx.cpp for GBomberman
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
#include "GRangeBx.hh"

namespace bomberman {
namespace gfx {

gdl::Image GRangeBx::texture_ = loadHelper<gdl::Image>("./assets/textures/rangebx.jpg");

GRangeBx::GRangeBx(float realX, float realY)
    : dlists_(DisplayLists::getInstance()),
      x_(realX), y_(realY)
{
}

void GRangeBx::draw(void)
{
    BindHelper::bind(this->texture_, RANGE);
    glPushMatrix();
    glTranslatef(this->x_, 0, this->y_);
    this->dlists_[TCUBE];
    glPopMatrix();
}

}}
