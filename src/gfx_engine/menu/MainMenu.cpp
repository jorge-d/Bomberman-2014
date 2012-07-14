//
// MainMenu.cpp for  in /home/sabbag_a/branlette/famille/maman
//
// Made by fares l'arabe
// Login   <sabbag_a@youporn.net>
//
// Started on  Thu May 26 17:14:23 2011 fares sabbagh
//

#include <iostream>
#include <GL/gl.h>
#include <Image.hpp>
#include "BindHelper.hh"
#include "GraphicsEngine.hh"
#include "GameEngine.hh"
#include "String.hh"
#include "MainMenu.hh"

namespace bomberman {
namespace gfx {

MainMenu::MainMenu(void)
{
    this->setBackground("./assets/menu/backgroundMainMenu.jpg");
    this->mode_ = bomberman::MAIN_MENU;
    this->trX = 0;
    this->pos_.x = 250;
    this->pos_.y = 300;
    this->pos_.z = 0;
}

MainMenu::~MainMenu(void)
{
}

    void
    MainMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;
      this->gfxString_.setText(this->gameEngine_->getMainMenuString());
      this->gfxString_.setFontSize(8.0f);
    }

void
MainMenu::update(void)
{
    static int flg = 0;
    int	newFrom;

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
MainMenu::drawBackground(void)
{
    BindHelper::bind(this->background_, MAIN_MENU_BG);
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
MainMenu::draw(void)
{
    this->drawBackground();
    this->drawZone();
    this->drawText();
    this->drawArrow();
}

}}
