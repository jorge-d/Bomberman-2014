//
// GEmpty.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:51:53 2011 arnaud mesureur
//

#include <iostream>

#include <gdl/Image.hpp>

#include "LoadHelper.hpp"
#include "BindHelper.hh"
#include "DisplayLists.hh"
#include "GEmpty.hh"

namespace bomberman {
namespace gfx {

gdl::Image GEmpty::texture_ = loadHelper<gdl::Image>("./assets/textures/grass.png");

GEmpty::GEmpty(float realX, float realY)
    : dlists_(DisplayLists::getInstance()),
      x_(realX), y_(realY)
{
}

void GEmpty::draw(void)
{
    BindHelper::bind(this->texture_, EMPTY);
    glPushMatrix();
    glTranslatef(this->x_, 0, this->y_);
    this->dlists_[TRECT];
    glPopMatrix();
}

}}
