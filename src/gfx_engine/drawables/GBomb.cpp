//
// GBomb.cpp for GBomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:51:53 2011 arnaud mesureur
//

#include <gdl/Model.hpp>

#include "LoadHelper.hpp"
#include "BindHelper.hh"
#include "DisplayLists.hh"
#include "GBomb.hh"

namespace bomberman {
namespace gfx {

gdl::Model GBomb::model_ = loadHelper<gdl::Model>("./assets/models/bomb.fbx");

GBomb::GBomb(AElement* e, float realX, float realY)
    : dlists_(DisplayLists::getInstance()),
      x_(realX), y_(realY)
{
    (void) e;
}

void GBomb::draw(void)
{
    BindHelper::reset();
    glPushMatrix();
    glTranslatef(this->x_, 0, this->y_);
    gdl::Model::Begin();
    this->model_.draw();
    gdl::Model::End();
    glPopMatrix();
}

}}
