//
// GPlayer.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:51:53 2011 arnaud mesureur
//

#include <gdl/Model.hpp>
#include <gdl/Clock.hpp>
#include <gdl/Color.hpp>

#include <iostream>

#include "BindHelper.hh"
#include "Game.hh"
#include "AElement.hh"
#include "APlayer.hh"
#include "GPlayer.hh"

#include "DisplayLists.hh"

namespace bomberman {
namespace gfx {


GPlayer::GPlayer(AElement* p, float realX, float realY)
    :	GPlayer_(p), x_(realX), y_(realY)
{
  this->model_ = gdl::Model::load("./assets/models/marvinLowLowPo.fbx");
  this->APlayer_ = dynamic_cast<APlayer *>(this->GPlayer_);
  this->model_.set_default_model_color(this->APlayer_->getColor());
  if (gdl::Model::cut_animation(this->model_, "Take 001", 36, 55, "Run") == false)
    std::cerr << "Wtf?" << std::endl;
}

void GPlayer::update(void)
{
    switch (this->GPlayer_->getDirection())
    {
    case bomberman::UP:
        this->r_ = (90 * 2) % 360;
        break;
    case bomberman::LEFT:
        this->r_ = (90 * 3) % 360;
        break;
    case bomberman::RIGHT:
        this->r_ = (90 * 1) % 360;
        break;
    case bomberman::DOWN:
        this->r_ = (90 * 4) % 360;
        break;
    default:
        break;
    }
    this->model_.update(*Game::getGameClock());
}

void GPlayer::draw(void)
{
    this->APlayer_ = dynamic_cast<APlayer *>(this->GPlayer_);

    BindHelper::reset();
    this->update();
    if (this->APlayer_->isMoving() == true)
      this->model_.play("Run", gdl::Anim::LOOP);
    else
      this->model_.stop_animation("Run");
    glPushMatrix();
    glTranslatef(this->x_, 0, this->y_);
    glRotatef(this->r_, 0.0f, 1.0f, 0.0f);
    this->model_.draw();
    glPopMatrix();
}

void
GPlayer::setData(AElement* e, float x, float y)
{
    this->GPlayer_ = e;
    this->x_ = x;
    this->y_ = y;
}
}}
