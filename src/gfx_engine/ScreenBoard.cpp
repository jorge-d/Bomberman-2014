//
// ScreenBoard.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 11:43:38 2011 arnaud mesureur
//

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>
#include <gdl/Image.hpp>

#include "BindHelper.hh"
#include "Human.hh"
#include "Map.hh"
#include "ScreenBoard.hh"
#include "DisplayLists.hh"
#include "APlayer.hh"
#include "CSplit.hh"
#include "String.hh"

#include <stdexcept>

namespace bomberman {
namespace gfx {

const int ScreenBoard::radius_ = 25;
int ScreenBoard::idGen_ = 1;


ScreenBoard::ScreenBoard(void)
    : id_(idGen_++),
      camera_(id_),
      isInitialized_(false),
      dlists_(DisplayLists::getInstance()),
      background_(gdl::Image::load("./assets/textures/bg.jpg"))
{
}

ScreenBoard::~ScreenBoard(void)
{
    Square::unload();
}

//////////////////////////////////////////
/// Public member functions
//////////////////////////////////////////

void
ScreenBoard::initialize(Map* map)
{
    this->map_ = map;
    this->player_ = map->getPlayer(this->id_);
    if (this->map_ != NULL && this->player_ != NULL)
        this->isInitialized_ = true;
}

void
ScreenBoard::update(void)
{
    if (this->isInitialized_ == true)
    {
        APlayer* p = this->map_->getPlayer(this->id_);
        int width = this->map_->getWidth();
        int height = this->map_->getHeight();
        int tmp;
        int baseX = (tmp = (p->getPosX() - this->radius_)) > 0 ? tmp : 0;
        int baseY = (tmp = (p->getPosY() - this->radius_)) > 0 ? tmp : 0;
        int maxX = (tmp = (p->getPosX() + this->radius_)) < width ? tmp : width;
        int maxY = (tmp = (p->getPosY() + this->radius_)) < height ? tmp : height;

        for (int y = baseY; y < maxY; ++y)
        {
            for (int x = baseX; x < maxX; ++x)
            {
                Square* s = new Square(this->id_, this->map_, x, y);
                this->board_.push_back(s);
            }
        }
    }
}

void
ScreenBoard::draw(void)
{
    //////////////////////////////////////////
    /// Replace camera
    //////////////////////////////////////////
    APlayer* p = this->map_->getPlayer(this->id_);
    this->camera_.initialize();
    this->drawBackground();
    this->camera_.update(p->getRealPosX() * Square::size,
                         p->getRealPosY() * Square::size);


    //////////////////////////////////////////
    /// Draw squares
    //////////////////////////////////////////
    std::list<Square*>::iterator it = this->board_.begin();
    for (; it != this->board_.end(); ++it)
    {
        (*it)->draw();
      	delete *it;
    }
    this->board_.clear();

    this->drawScore();

    if (Human::getNbHumans() > 1)
        this->drawSplitLine();
}

void
ScreenBoard::drawBackground(void)
{
    BindHelper::bind(this->background_, SCREENBOARD_BG);
    this->dlists_[TBACKG];
}

void
ScreenBoard::drawSplitLine(void) const
{
    if (this->id_ == 1)
        this->dlists_[CSPLIT];
}

void
ScreenBoard::drawScore(void) const
{
    gdl::Window w;
    unsigned int width = w.getWidth();
    unsigned int height = w.getHeight();

    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0f, width, 0.0f, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glColor4ub(42, 42, 42, 230);

    glBegin(GL_QUADS);
    glVertex2i(0, -height);
    glVertex2i(0, height / 10);
    glVertex2i(width, height / 10);
    glVertex2i(width, -height);
    glEnd();

    gfx::String tmp(this->player_->getScore(), 14);
    tmp.printText(width / 2, 40, 0);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glColor3f(1.0f,1.0f,1.0f);
}


}}
