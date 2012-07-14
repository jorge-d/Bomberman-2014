//
// GWall.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 09:27:15 2011 arnaud mesureur
//

#include <cstdlib>
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include <gdl/Image.hpp>

#include "LoadHelper.hpp"
#include "BindHelper.hh"
#include "IDrawable.hh"
#include "GWall.hh"

namespace bomberman {
namespace gfx {

gdl::Image GWall::texture_ = loadHelper<gdl::Image>("./assets/textures/bricks.png");

GWall::GWall(float realX, float realY)
    : dlists_(DisplayLists::getInstance()),
      x_(realX), y_(realY)
{
}

void GWall::draw(void)
{
    BindHelper::bind(this->texture_, WALL);
    glPushMatrix();

    glTranslatef(this->x_, 0, this->y_);
    this->dlists_[TCUBE];

    glPopMatrix();
}

}}
