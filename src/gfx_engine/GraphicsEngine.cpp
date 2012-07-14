//
// GraphicsEngine.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 17:12:45 2011 arnaud mesureur
//

#include <cstdlib>
#include <GL/gl.h>
#include <gdl/Image.hpp>

#include "GraphicsEngine.hh"
#include "Map.hh"
#include "Human.hh"

#include "Vector3f.hh"
#include "IPrimitive.hh"
#include "TRect.hh"
#include "TCube.hh"
#include "CSplit.hh"
#include "TBackG.hh"
#include "DisplayLists.hh"

namespace bomberman {

bool fullscreen = false;

//////////////////////////////////////////
/// Constructor / Destructor
//////////////////////////////////////////

GraphicsEngine::GraphicsEngine(Game* parent)
    : Engine(parent),
      dlists_(gfx::DisplayLists::getInstance()),
      multiplayer_(false),
      reload_(false)
{
}

GraphicsEngine::~GraphicsEngine(void)
{
}

//////////////////////////////////////////
/// Public member functions
//////////////////////////////////////////

void
GraphicsEngine::initialize(void)
{
    //////////////////////////////////////////
    /// init window
    //////////////////////////////////////////
    if (bomberman::fullscreen == true)
    {
        this->window_.setFullscreen(true);
    }
    else
    {
        this->window_.setWidth(bomberman::defaultWinW);
        this->window_.setHeight(bomberman::defaultWinH);
    }
    this->window_.create();

    //////////////////////////////////////////
    /// init display lists
    //////////////////////////////////////////
    this->dlists_.createList(gfx::TCUBE, new gfx::TCube(gfx::Square::size));
    this->dlists_.createList(gfx::TRECT, new gfx::TRect(gfx::Square::size,
                                                        gfx::Square::size));
    this->dlists_.createList(gfx::CSPLIT, new gfx::CSplit());
    this->dlists_.createList(gfx::TBACKG, new gfx::TBackG());

    this->menu_.initialize(this->gameEngine_);
}

void
GraphicsEngine::update(void)
{
    if (this->gameEngine_->getMenuStatus() == PLAYING)
    {
        if (this->reload_ == false)
            this->reload();
        this->boardP1_.update();
        if (this->multiplayer_ == true)
            this->boardP2_.update();
    }
    else
    {
        this->menu_.update();
        this->reload_ = false;
    }
}

void
GraphicsEngine::draw(void)
{
    if (this->gameEngine_->getMenuStatus() == PLAYING)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->boardP1_.draw();
        if (this->multiplayer_ == true)
            this->boardP2_.draw();
        glClearDepth(1.0f);
    }
    else
    {
      this->menu_.draw();
    }
}

void
GraphicsEngine::unload(void)
{
    this->dlists_.destroyInstance();
}

//////////////////////////////////////////
/// Private member functions
//////////////////////////////////////////

void
GraphicsEngine::reload(void)
{
    this->multiplayer_ = Human::getNbHumans() > 1 ? true : false;
    this->boardP1_.initialize(this->gameEngine_->getMap());
    if (this->multiplayer_ == true)
        this->boardP2_.initialize(this->gameEngine_->getMap());
    this->reload_ = true;
}

}
