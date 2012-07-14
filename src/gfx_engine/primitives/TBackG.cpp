//
// TBackG.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#include <GL/gl.h>
#include <GL/glu.h>

#include "gdl/Window.hpp"

#include "GraphicsEngine.hh"
#include "TBackG.hh"
#include "Square.hh"

namespace bomberman {
namespace gfx {

void
TBackG::compute(void)
{
    gdl::Window win;
    int w = win.getWidth();
    int h = win.getHeight();

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0f, h, 0.0f, w);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, -w);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, w);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(h, w);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(h, -w);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
}

}}
