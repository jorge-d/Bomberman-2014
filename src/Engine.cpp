//
// engine.cpp for game engine in /home/mesure_a/workspace/
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Thu May  5 16:44:53 2011 arnaud mesureur
//

#include "Engine.hh"
#include "Game.hh"

namespace bomberman {

Engine::Engine(Game* parent)
    : parent_(parent)
{
}

Engine::~Engine(void)
{
}

void
Engine::attachEngine(GameEngine* e)
{
    this->gameEngine_ = e;
}

void
Engine::attachEngine(GraphicsEngine* e)
{
    this->graphicsEngine_ = e;
}

void
Engine::attachEngine(SoundEngine* e)
{
    this->soundEngine_ = e;
}

}
