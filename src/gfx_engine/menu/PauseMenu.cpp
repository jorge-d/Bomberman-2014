//
// PauseMenu.cpp for  in /home/sabbag_a/bomberman-2014-rodrig_d/examples/tuto
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Thu May 26 17:14:23 2011 fares sabbagh

//

#include <iostream>
#include <GL/gl.h>
#include <Image.hpp>
#include <Window.hpp>

#include "GraphicsEngine.hh"
#include "GameEngine.hh"
#include "String.hh"
#include "PauseMenu.hh"
#include "BindHelper.hh"

namespace bomberman
{
  namespace gfx
  {
    PauseMenu::PauseMenu(void) :
      drawBack_(true)
    {
      this->setBackground("./assets/menu/backgroundPause.png");
      this->mode_ = bomberman::GAME_PAUSED;
      this->trX = 0;
      this->pos_.x = 300;
      this->pos_.y = 340;
      this->pos_.z = 0;
    }

    PauseMenu::~PauseMenu(void)
    {
    }

    void
    PauseMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;
      this->gfxString_.setText(this->gameEngine_->getPauseMenuString());
    }

    void
    PauseMenu::reset(bool newVal)
    {
      this->drawBack_ = newVal;
    }

    void
    PauseMenu::update(void)
    {
      static int flg = 0;
      int	newFrom;
      gdl::Window w;

      glViewport(0, 0, w.getWidth(), w.getHeight());
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt (0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

      this->cursor_ = this->gameEngine_->getCursor();
      flg = (this->trX <= -50 ? 1 : this->trX >= 0 ? 0 : flg);
      this->trX += (flg ? 3 : -3);
      this->from_ = ((newFrom = (this->cursor_ - (this->nElemH - 1))) <= 0 ? 0 : newFrom);
    }

    void
    PauseMenu::drawBackground(void)
    {
      glEnable(GL_BLEND);
      glEnable(GL_TEXTURE_2D);
      BindHelper::bind(this->background_, ENDGAME_MENU_BG);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glAlphaFunc(GL_GREATER, 1);
      glPushMatrix();
      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex2f(200, 425);
      glTexCoord2f(0, 1); glVertex2f(200, 175);
      glTexCoord2f(1, 1); glVertex2f(600, 175);
      glTexCoord2f(1, 0); glVertex2f(600, 425);
      glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
    }

    void
    PauseMenu::drawZone(void)
    {
      glDisable(GL_TEXTURE_2D);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glColor4ub(42, 42, 42, 200);
      glBegin(GL_QUADS);
      glVertex2i(0, 600);
      glVertex2i(0, 0);
      glVertex2i(800, 0);
      glVertex2i(800, 600);
      glEnd();
      glColor3f(1.0f, 1.0f, 1.0f);
      glDisable(GL_BLEND);
      glDisable(GL_TEXTURE_2D);
    }

    void
    PauseMenu::draw(void)
    {
      this->drawBackground();
      if (this->drawBack_)
	this->drawZone();
      this->drawText();
      this->drawArrow();
    }
  }
}
