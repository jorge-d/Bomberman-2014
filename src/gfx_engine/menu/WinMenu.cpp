//
// WinMenu.cpp for  in /home/sabbag_a/bomberman-2014-rodrig_d/examples/tuto
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
#include "BindHelper.hh"
#include "String.hh"
#include "WinMenu.hh"

namespace bomberman
{
  namespace gfx
  {
    WinMenu::WinMenu(void) :
      lastWinner_(bomberman::IA_WON)
    {
      this->trX = -50;
      this->pos_.x = 380;
      this->pos_.y = 200;
      this->pos_.z = 0;
    }

    WinMenu::~WinMenu(void)
    {
    }

    void
    WinMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;
      this->setBackground("assets/menu/backgroundWin.jpg");
    }

    void
    WinMenu::update(void)
    {
      gdl::Window w;

      glViewport(0, 0, w.getWidth(), w.getHeight());
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 1.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt (0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

      this->mode_ = this->gameEngine_->getMenuStatus();
      this->gfxString_.setText(this->gameEngine_->getNickname());
      this->cursor_ = this->gameEngine_->getCursor();
      if (this->lastWinner_ != this->mode_)
      {
	if (this->mode_ == bomberman::PLAYER_1_WON)
	  this->introString_.setText("Player 1 won, type your nickname");
	else
	  this->introString_.setText("Player 2 won, type your nickname");
	this->lastWinner_ = this->mode_;
      }
    }

    void
    WinMenu::drawBackground(void)
    {
      glEnable(GL_TEXTURE_2D);
      BindHelper::bind(this->background_, ENDGAME_MENU_BG);
      glPushMatrix();
      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex2f(0, 600);
      glTexCoord2f(0, 1); glVertex2f(0, 0);
      glTexCoord2f(1, 1); glVertex2f(800, 0);
      glTexCoord2f(1, 0); glVertex2f(800, 600);
      glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
    }

    void
    WinMenu::drawText(void)
    {
      this->introString_.printText(50, 325, 0);
      this->gfxString_.printText(this->pos_.x, this->pos_.y, 0);
    }

    void
    WinMenu::draw(void)
    {
      this->drawBackground();
      this->drawText();
    }
  }
}
