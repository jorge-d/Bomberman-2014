//
// Menu.cpp for  in /home/sabbag_a/bomberman-2014-rodrig_d/examples/tuto
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Wed May 25 21:51:05 2011 fares sabbagh
//

#include <iostream>
#include <Image.hpp>
#include <algorithm>
#include <map>
#include "GameEngine.hh"
#include "String.hh"
#include "LoadHelper.hpp"
#include "Menu.hh"
#include "IntroSceneMenu.hh"
#include "MainMenu.hh"
#include "NewGameMenu.hh"
#include "PauseMenu.hh"
#include "LoadMenu.hh"
#include "ScoreMenu.hh"
#include "WinMenu.hh"
#include "LooseMenu.hh"
#include "BindHelper.hh"

namespace bomberman {
  namespace gfx {

    gdl::Image Menu::arrow_ = loadHelper<gdl::Image>("./assets/menu/arrow.png");

    Menu::Menu():
      nElemH(5)
    {
    }

    Menu::~Menu(void)
    {
    }

    void		Menu::initialize(bomberman::GameEngine *e)
    {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 1.0f);

      this->menu_[bomberman::INTRODUCTION_SCENE] = new IntroSceneMenu();
      this->menu_[bomberman::MAIN_MENU] = new MainMenu();
      this->menu_[bomberman::CHOOSE_MAP_1P] = new NewGameMenu();
      this->menu_[bomberman::GAME_PAUSED] = new PauseMenu();
      this->menu_[bomberman::LOAD_GAME] = new LoadMenu();
      this->menu_[bomberman::DISPLAY_SCORES] = new ScoreMenu();
      this->menu_[bomberman::PLAYER_1_WON] = new WinMenu();
      this->menu_[bomberman::IA_WON] = new LooseMenu();

      this->gameEngine_ = e;
      this->mode_ = this->gameEngine_->getMenuStatus();
      std::map<enum bomberman::menu, IMenu *>::iterator it = this->menu_.begin();
      for (; it != this->menu_.end(); ++it)
	(*it).second->initialize(e);
    }

    void		Menu::setBackground(const char *filename)
    {
      this->background_ = loadHelper<gdl::Image>(filename);
    }

    void		Menu::update(void)
    {
      this->mode_ = this->gameEngine_->getMenuStatus();
      if (this->mode_ == bomberman::CHOOSE_MAP_2P)
	this->mode_ = bomberman::CHOOSE_MAP_1P;
      else if (this->mode_ == bomberman::PLAYER_2_WON)
	this->mode_ = bomberman::PLAYER_1_WON;
      if (this->mode_ != bomberman::GAME_PAUSED)
	dynamic_cast<PauseMenu*>(this->menu_[bomberman::GAME_PAUSED])->reset(true);
      if (this->menu_.count(this->mode_) > 0)
	this->menu_[this->mode_]->update();
    }

    void		Menu::draw(void)
    {
      if (this->menu_.count(this->mode_) > 0)
	this->menu_[this->mode_]->draw();
      if (this->mode_ == bomberman::GAME_PAUSED)
	dynamic_cast<PauseMenu*>(this->menu_[bomberman::GAME_PAUSED])->reset(false);
    }

    void
    Menu::drawZone(void)
    {
      glPushMatrix();
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glBegin(GL_QUADS);
      glColor4ub(204, 204, 204, 100);
      glVertex2f(200, 600);
      glVertex2f(200, 0);
      glVertex2f(600, 0);
      glVertex2f(600, 600);
      glColor3f(1.0f, 1.0f, 1.0f);
      glEnd();
      glDisable(GL_BLEND);
      glPopMatrix();
    }

    void
    Menu::drawText(void)
    {
      float	size = this->gfxString_.getFontSize();
      int	i = 0;

      for (unsigned int idx = this->from_; (idx < (this->from_ + this->nElemH)) &&
	     idx < this->gfxString_.getNbrStrings(); ++i, ++idx)
      {
	if (idx == this->cursor_)
	  this->gfxString_.setFontSize(size + 5);
	this->gfxString_.printText(this->pos_.x, this->pos_.y - (i * this->gap), idx);
	if (idx == this->cursor_)
	  this->gfxString_.setFontSize(size);
      }
    }

    void
    Menu::drawArrow(void)
    {
      int x = this->pos_.x - this->arrow_.getWidth();
      int cursorReal = this->cursor_ >= this->nElemH ? this->nElemH - 1 : this->cursor_;
      int y = (this->pos_.y - cursorReal * this->gap) + (this->arrow_.getHeight() / 2);

      glEnable(GL_TEXTURE_2D);
      glEnable(GL_BLEND);
      BindHelper::bind(this->arrow_, ARROW_MENU);
      glPushMatrix();
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glAlphaFunc(GL_GREATER, 1);
      glTranslatef(this->trX, 0.0f, 0.0f);
      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex2f(x, y);
      glTexCoord2f(0, 1); glVertex2f(x, y - this->arrow_.getHeight());
      glTexCoord2f(1, 1); glVertex2f(x + this->arrow_.getWidth(), y - this->arrow_.getHeight());
      glTexCoord2f(1, 0); glVertex2f(x + this->arrow_.getWidth(), y);
      glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
    }
  }
}
