//
// NewGameMenu.cpp for  in /home/sabbag_a/bomberman-2014-rodrig_d/examples/tuto
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Thu May 26 17:14:23 2011 fares sabbagh
// Last update Sun Jun  5 23:00:35 2011 fares sabbagh
//

#include <iostream>
#include <GL/gl.h>
#include <Image.hpp>

#include "String.hh"
#include "GraphicsEngine.hh"
#include "GameEngine.hh"
#include "ABombxml.hh"
#include "ScoreMenu.hh"
#include "Scores.hh"
#include "BindHelper.hh"
#include "Constants.hh"

namespace bomberman
{
  namespace gfx
  {
    ScoreMenu::ScoreMenu(void) :
      indent_("")
    {
      this->setBackground("./assets/menu/backgroundNewGame.jpg");
      this->mode_ = bomberman::DISPLAY_SCORES;
      this->nElemH = 10;
      this->from_ = 0;
      for (int i = 0; i < 5; ++i)
	this->indent_ += " ";
      this->board_.setText(" Nick" + this->indent_ + "   " +
			   "Date" + this->indent_ + "   Score");
      this->pos_.x = 95;
      this->pos_.y = 525;
      this->pos_.z = 0;
    }

    ScoreMenu::~ScoreMenu(void)
    {
    }

    void
    ScoreMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;
      this->loadText();
    }

    void
    ScoreMenu::loadText(void)
    {
      std::list<score *> tmp = this->gameEngine_->getScoreList();

      if (this->gfxString_.getNbrStrings() != tmp.size() || tmp.size() == 1)
      {
	this->gfxString_.clear();
	std::list<score *>::const_iterator it = tmp.begin();
	for (; it != tmp.end(); ++it)
	  if (*it != NULL)
	  {
	    std::string	tmpString;

	    tmpString = ((*it)->name.substr(0, 5)) +
	      this->indent_ +
	      (*it)->date +
	      this->indent_ +
	      NumberToString<int>((*it)->score);
	    this->gfxString_.addText(tmpString);
	  }
      }
      if (!this->gfxString_.getNbrStrings())
      {
	this->gfxString_.setText("Empty");
	this->pos_.x = 350;
	this->pos_.y = 300;
	this->gfxString_.setFontSize(15);
      }
      else
      {
	this->pos_.x = 95;
	this->pos_.y = 525;
	this->gfxString_.setFontSize(10);
      }
    }

    void
    ScoreMenu::update(void)
    {
      this->loadText();
    }

    void
    ScoreMenu::drawBackground(void)
    {
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
    ScoreMenu::drawZone(void)
    {
      glPushMatrix();
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glBegin(GL_QUADS);
      glColor4ub(42, 42, 42, 100);
      glVertex2f(100, 600);
      glVertex2f(100, 0);
      glVertex2f(700, 0);
      glVertex2f(700, 600);
      glColor3f(1.0f, 1.0f, 1.0f);
      glEnd();
      glDisable(GL_BLEND);
      glPopMatrix();
    }

    void
    ScoreMenu::drawText(void)
    {
      for (unsigned int i = this->from_; (i < this->nElemH) &&
	     i < this->gfxString_.getNbrStrings(); ++i)
      {
	if (!i && (this->gfxString_.getText(0) != "Empty"))
	  this->board_.printText(pos_.x, pos_.y + this->gap, 0);
	this->gfxString_.printText(this->pos_.x, this->pos_.y - (i * this->gap), i);
      }
    }

    void
    ScoreMenu::draw(void)
    {
      this->drawBackground();
      this->drawZone();
      this->drawText();
    }
  }
}
