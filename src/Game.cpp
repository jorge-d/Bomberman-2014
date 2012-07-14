//
// Game.cpp for Bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Tue May 10 20:59:25 2011 arnaud mesureur
//

#include <cstdlib>

#include "gdl/Game.hpp"

#include "Game.hh"
#include "Exception.hh"

namespace bomberman {

//////////////////////////////////////////
/// Static members
//////////////////////////////////////////

gdl::GameClock* Game::gameClockPtr_ = NULL;
int Game::nbInstance_ = 0;

gdl::GameClock*
Game::getGameClock(void)
{
    return Game::gameClockPtr_;
}


//////////////////////////////////////////
/// Public members
//////////////////////////////////////////


Game::Game(void)
    : gdl::Game(),
      gameEngine_(new GameEngine(this)),
      graphicsEngine_(new GraphicsEngine(this)),
      soundEngine_(new SoundEngine(this))
{
  if (Game::nbInstance_ == 0)
    {
        this->gameEngine_->attachEngine(this->graphicsEngine_);
        this->gameEngine_->attachEngine(this->soundEngine_);

        this->graphicsEngine_->attachEngine(this->gameEngine_);
        this->graphicsEngine_->attachEngine(this->soundEngine_);

        this->soundEngine_->attachEngine(this->gameEngine_);
        this->soundEngine_->attachEngine(this->graphicsEngine_);

        Game::gameClockPtr_ = &this->gameClock_;
        ++Game::nbInstance_;
    }
    else
    {
        this->die("Error: Game is already instanciate");
    }
}

Game::~Game(void)
{
    delete this->gameEngine_;
    delete this->graphicsEngine_;
    delete this->soundEngine_;
    Game::gameClockPtr_ = NULL;
    --Game::nbInstance_;
}

void
Game::initialize(void)
{
    this->gameEngine_->initialize();
    this->graphicsEngine_->initialize();
    this->soundEngine_->initialize();
}

void
Game::update(void)
{
    this->gameEngine_->update();
    this->graphicsEngine_->update();
    this->soundEngine_->update();
}

void
Game::draw(void)
{
    this->graphicsEngine_->draw();
    this->window_.display();
}

void
Game::unload(void)
{
    this->gameEngine_->unload();
    this->graphicsEngine_->unload();
    this->soundEngine_->unload();
}

gdl::Input&
Game::getInput(void)
{
    return this->input_;
}

gdl::GameClock&
Game::getClock(void)
{
  return this->gameClock_;
}

void
Game::die(const char* message) const
{
    throw Exception(message);
}

}
