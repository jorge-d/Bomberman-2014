//
// CSplit.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#include <GL/gl.h>
#include <GL/glu.h>

#include "GraphicsEngine.hh"
#include "Vector3f.hh"
#include "CSplit.hh"

namespace bomberman {
namespace gfx {

void
CSplit::compute(void)
{
    gdl::Window win;
    unsigned int w = win.getWidth();
    unsigned int h = win.getHeight();

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0f, w, 0.0f, h);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);
    glColor3ub(100, 100, 100);

    glBegin(GL_QUADS);
    glVertex2i(0, -h);
    glVertex2i(0, h);
    glVertex2i(10, h);
    glVertex2i(10, -h);
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glColor3ub(255, 255, 255);
}

}}
