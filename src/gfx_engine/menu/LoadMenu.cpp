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
#include "LoadMenu.hh"
#include "BindHelper.hh"

namespace bomberman
{
  namespace gfx
  {
    LoadMenu::LoadMenu(void)
    {
      this->mode_ = bomberman::LOAD_GAME;
      this->setBackground("./assets/menu/backgroundNewGame.jpg");
      this->trX = 0;
      this->pos_.x = 250;
      this->pos_.y = 300;
      this->pos_.z = 0;
    }

    LoadMenu::~LoadMenu(void)
    {
    }

    void
    LoadMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;
      this->loadText();
    }

    void
    LoadMenu::loadText(void)
    {
      std::vector<ABombxml *> tmp = this->gameEngine_->getSavesList();

      if (this->gfxString_.getNbrStrings() != tmp.size())
      {
	this->gfxString_.clear();
	std::vector<ABombxml *>::const_iterator it = tmp.begin();
	for (; it != tmp.end(); ++it)
	  if (*it != NULL)
	    this->gfxString_.addText((*it)->getMapName());
      }
    }

    void
    LoadMenu::update(void)
    {
      int	newFrom;
      static int flg = 0;

      this->cursor_ = this->gameEngine_->getCursor();
      flg = (this->trX <= -50 ? 1 : this->trX >= 0 ? 0 : flg);
      this->trX += (flg ? 3 : -3);
      this->from_ = ((newFrom = (this->cursor_ - (this->nElemH - 1))) <= 0 ? 0 : newFrom);
      this->loadText();
    }

    void
    LoadMenu::drawBackground(void)
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
    LoadMenu::draw(void)
    {
      this->drawBackground();
      this->drawZone();
      this->drawText();
      this->drawArrow();
    }
  }
}
