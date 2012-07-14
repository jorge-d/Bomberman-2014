//
// IntroSceneMenu.cpp for  in /home/sabbag_a/bomberman-2014-rodrig_d/examples/tuto
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Thu May 26 17:14:23 2011 fares sabbagh
// Last update Sun Jun  5 22:25:31 2011 fares sabbagh
//

#include <iostream>
#include <GL/gl.h>
#include <Model.hpp>
#include "Game.hh"
#include "String.hh"
#include "GraphicsEngine.hh"
#include "GameEngine.hh"
#include "ABombxml.hh"
#include "IntroSceneMenu.hh"
#include "BindHelper.hh"
#include "LoadHelper.hpp"
#include "DisplayLists.hh"

namespace bomberman
{
  namespace gfx
  {
    IntroSceneMenu::IntroSceneMenu(void) :
      rotB_(0, 0, 0),
      dlists_(DisplayLists::getInstance())
    {
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);

      this->mode_ = bomberman::INTRODUCTION_SCENE;
      this->setBackground("./assets/menu/backgroundIntro.jpg");
      this->marvin_ = loadHelper<gdl::Model>("assets/models/marvinLowLowPo.fbx");
      this->bomb_ = loadHelper<gdl::Model>("assets/models/bomb.fbx");
      gdl::Model::cut_animation(this->marvin_, "Take 001", 36, 55, "Run");
    }

    IntroSceneMenu::~IntroSceneMenu(void)
    {
    }

    void
    IntroSceneMenu::initialize(bomberman::GameEngine *e)
    {
      this->gameEngine_ = e;
    }

    void
    IntroSceneMenu::update(void)
    {
      this->marvin_.update(*Game::getGameClock());
      this->marvin_.play("Run");
      this->rotB_.x = (static_cast<int>(this->rotB_.x) - 20) % 360;
    }

    void
    IntroSceneMenu::drawBackground(void)
    {
      glDisable(GL_DEPTH_TEST);
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      gluOrtho2D(0.0f, 1, 0.0f, 1);
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      glLoadIdentity();

      BindHelper::bind(this->background_, INTRO_MENU_BG);
      glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex2f(0, 1);
      glTexCoord2f(0, 1); glVertex2f(0, 0);
      glTexCoord2f(1, 1); glVertex2f(1, 0);
      glTexCoord2f(1, 0); glVertex2f(1, 1);
      glEnd();

      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
      glEnable(GL_DEPTH_TEST);
    }

    void
    IntroSceneMenu::drawMarvin(void)
    {
      BindHelper::reset();
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(70.0f, 800.f/600.0f, 0.1f, 10000.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0.0f, 1000.0f, 3000.0f,
		0.0f, -1.0f, -1.0f,
		0.0f, 1.0f, 0.0f);

      glPushMatrix();
      glTranslatef(0, 0, 0);
      glRotatef(90, 0.0f, 1.0f, 0.0f);
      this->marvin_.draw();
      glPopMatrix();
    }

    void
    IntroSceneMenu::drawBomb(void)
    {
      glPushMatrix();
      glTranslatef(450, 100, 0);
      glRotatef(this->rotB_.x, 0.0f, 0.0f, 1.0f);
      this->bomb_.draw();
      glPopMatrix();
    }

    void
    IntroSceneMenu::draw(void)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
      glClearDepth(1.0f);

      this->drawBackground();
      this->drawMarvin();
      this->drawBomb();
    }
  }
}
