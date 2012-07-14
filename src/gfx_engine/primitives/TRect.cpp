//
// TRect.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#include <GL/gl.h>
#include <GL/glu.h>

#include "TRect.hh"
#include "Square.hh"

namespace bomberman {
namespace gfx {

TRect::TRect(float width, float height)
    : w_(width / 2), h_(height / 2)
{
}

void
TRect::compute(void)
{
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->w_,  -this->h_, -this->w_);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->w_,  -this->h_,  this->w_);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( this->w_,  -this->h_,  this->w_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( this->w_,  -this->h_, -this->w_);

    glEnd();
}

}}
