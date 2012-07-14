//
// TCube.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#include <GL/gl.h>
#include <GL/glu.h>

#include "TCube.hh"
#include "Square.hh"

namespace bomberman {
namespace gfx {

TCube::TCube(float size)
    : s_(size / 2)
{
}

void
TCube::compute(void)
{
    glBegin(GL_QUADS);

    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->s_, -this->s_,  this->s_);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( this->s_, -this->s_,  this->s_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( this->s_,  this->s_,  this->s_);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->s_,  this->s_,  this->s_);

    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->s_, -this->s_, -this->s_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->s_,  this->s_, -this->s_);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( this->s_,  this->s_, -this->s_);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( this->s_, -this->s_, -this->s_);

    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->s_,  this->s_, -this->s_);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->s_,  this->s_,  this->s_);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( this->s_,  this->s_,  this->s_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( this->s_,  this->s_, -this->s_);

    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( this->s_, -this->s_, -this->s_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( this->s_,  this->s_, -this->s_);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( this->s_,  this->s_,  this->s_);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( this->s_, -this->s_,  this->s_);

    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-this->s_, -this->s_, -this->s_);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-this->s_, -this->s_,  this->s_);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-this->s_,  this->s_,  this->s_);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-this->s_,  this->s_, -this->s_);

    glEnd();
}

}}
