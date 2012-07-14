//
// SoundEngine.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Wed May 11 17:13:53 2011 arnaud mesureur
//

#include <iostream>
#include <SFML/Audio.hpp>

#include "GameEngine.hh"
#include "SoundEngine.hh"

namespace bomberman {

SoundEngine::SoundEngine(Game* parent)
    : Engine(parent),
      currentTrack_(BLANK)
{
}

SoundEngine::~SoundEngine(void)
{
}

void
SoundEngine::initialize(void)
{
    this->playlist_[EXPLOSION] = new sf::Music;
    this->playlist_[EXPLOSION]->OpenFromFile("./assets/sfx/explosion.wav");

    this->playlist_[BREAK_BOX] = new sf::Music;
    this->playlist_[BREAK_BOX]->OpenFromFile("./assets/sfx/breakbox.wav");

    this->playlist_[POWER_UP] = new sf::Music;
    this->playlist_[POWER_UP]->OpenFromFile("./assets/sfx/powerup.wav");

    this->playlist_[MENU] = new sf::Music;
    if (this->playlist_[MENU]->OpenFromFile("./assets/sfx/menu.wav"))
        this->playlist_[MENU]->SetLoop(true);

    this->playlist_[GAME] = new sf::Music;
    if (this->playlist_[GAME]->OpenFromFile("./assets/sfx/game.wav"))
        this->playlist_[GAME]->SetLoop(true);

    this->playlist_[INTRO] = new sf::Music;
    if (this->playlist_[INTRO]->OpenFromFile("./assets/sfx/tintin.wav"))
        this->playlist_[INTRO]->SetLoop(true);
}

void
SoundEngine::update(void)
{
    // play matching song
    if (this->gameEngine_->getMenuStatus() == PLAYING)
    {
        // stop current song
        if (this->currentTrack_ != GAME)
            this->stop(this->currentTrack_);
        this->play(GAME);
        this->currentTrack_ = GAME;
    }
    else if (this->gameEngine_->getMenuStatus() == INTRODUCTION_SCENE)
    {
        // stop current song
        if (this->currentTrack_ != INTRO)
            this->stop(this->currentTrack_);
        this->play(INTRO);
        this->currentTrack_ = INTRO;
    }
    else
    {
        // stop current song
        if (this->currentTrack_ != MENU)
            this->stop(this->currentTrack_);
        this->play(MENU);
        this->currentTrack_ = MENU;
    }
}

void
SoundEngine::unload(void)
{
    std::map<playable_id, sf::Music*>::iterator it = this->playlist_.begin();
    for (; it != this->playlist_.end(); ++it)
        delete it->second;
}

void
SoundEngine::play(playable_id id)
{
    std::map<playable_id, sf::Music*>::iterator
        sfx = this->playlist_.find(id);

    if (sfx != this->playlist_.end())
    {
        if (sfx->second->GetStatus() != sf::Sound::Playing)
            sfx->second->Play();
    }
}

void
SoundEngine::stop(playable_id id)
{
    std::map<playable_id, sf::Music*>::iterator
        sfx = this->playlist_.find(id);

    if (sfx != this->playlist_.end())
    {
        if (sfx->second->GetStatus() != sf::Sound::Stopped)
            sfx->second->Stop();
    }
}

}
