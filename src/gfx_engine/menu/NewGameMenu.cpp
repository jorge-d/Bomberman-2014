//
// NewGameMenu.cpp for  in /home/sabbag_a/bomberman-2014-rodrig_d/examples/tuto
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Thu May 26 17:14:23 2011 fares sabbagh

//

#include <iostream>
#include <GL/gl.h>
#include <Image.hpp>

#include "String.hh"
#include "GraphicsEngine.hh"
#include "GameEngine.hh"
#include "ABombxml.hh"
#include "NewGameMenu.hh"
#include "BindHelper.hh"

namespace bomberman
{
  namespace gfx
  {
    NewGameMenu::NewGameMenu(void)
    {
      this->mode_ = bomberman::MAIN_MENU;
      this->setBackground("./assets/menu/backgroundNewGame.jpg");
      this->trX = 0;
    }

    NewGameMenu::~NewGameMenu(void)
    {
    }

    void
    NewGameMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;

      std::vector<ABombxml *> tmp = this->gameEngine_->getMapList();
      std::vector<ABombxml *>::const_iterator it = tmp.begin();
      for (; it != tmp.end(); ++it)
      {
	if (*it == NULL)
	  this->gfxString_.addText("Generate Random Map");
	else
	  this->gfxString_.addText((*it)->getMapName());
      }
      this->gfxString_.setFontSize(10);
    }

    void
    NewGameMenu::update(void)
    {
      int	newFrom;
      static int flg = 0;

      this->cursor_ = this->gameEngine_->getCursor();
      flg = (this->trX <= -50 ? 1 : this->trX >= 0 ? 0 : flg);
      this->trX += (flg ? 3 : -3);
      this->pos_.x = 200;
      this->pos_.y = 300;
      this->from_ = ((newFrom = (this->cursor_ - (this->nElemH - 1))) <= 0 ? 0 : newFrom);
    }

    void
    NewGameMenu::drawBackground(void)
    {
      glEnable(GL_TEXTURE_2D);
      BindHelper::bind(this->background_, NEW_GAME_MENU_BG);
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
    NewGameMenu::drawZone(void)
    {
      glEnable(GL_BLEND);
      glPushMatrix();
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glBegin(GL_QUADS);
      glColor4ub(204, 204, 204, 100);
      glVertex2f(100, 600);
      glVertex2f(100, 0);
      glVertex2f(700, 0);
      glVertex2f(700, 600);
      glColor3f(1.0f, 1.0f, 1.0f);
      glEnd();
      glPopMatrix();
      glDisable(GL_BLEND);
    }

    void
    NewGameMenu::draw(void)
    {
      this->drawBackground();
      this->drawZone();
      this->drawText();
      this->drawArrow();
    }
  }
}
