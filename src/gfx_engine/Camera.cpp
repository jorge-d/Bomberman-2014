//
// Camera.cpp for Bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sat May 21 04:22:56 2011 arnaud mesureur
//

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "gdl/Window.hpp"
#include "Human.hh"
#include "Camera.hh"

namespace bomberman {
namespace gfx {

const float Camera::fovy_ = 70.0f;
const float Camera::zNear_ = 1.0f;
const float Camera::zFar_ = 10000.0f;

const Vector3f Camera::eye_ = Vector3f(0.0f, 5000.0f, 2000.0f);
const Vector3f Camera::center_ = Vector3f(0.0f, -1.0f, 0.0f);
const Vector3f Camera::up_ = Vector3f(0.0f, 1.0f, 0.0f);

//////////////////////////////////////////
/// Public member functions
//////////////////////////////////////////

Camera::Camera(int id)
    : id_(id)
{
}

void
Camera::initialize(void) const
{
    bool multi = Human::getNbHumans() > 1 ? true : false;
    float w = this->win_.getWidth();
    float h = this->win_.getHeight();

    //////////////////////////////////////////
    /// Enable split screen in multi mode
    //////////////////////////////////////////
    if (multi == true)
        this->setMultiViewPort();

    //////////////////////////////////////////
    /// Camera Frustrum
    //////////////////////////////////////////
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Camera::fovy_, (multi ? (w / 2) : w) / h,
                   Camera::zNear_, Camera::zFar_);

    //////////////////////////////////////////
    /// Camera position
    //////////////////////////////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Camera::eye_.x, Camera::eye_.y, Camera::eye_.z,
              Camera::center_.x, Camera::center_.y, Camera::center_.z,
              Camera::up_.x, Camera::up_.y, Camera::up_.z);

    //////////////////////////////////////////
    /// Enable depth tests
    //////////////////////////////////////////
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void
Camera::update(float x, float y) const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Camera::eye_.x + x, Camera::eye_.y, Camera::eye_.z + y,
              Camera::center_.x + x, Camera::center_.y, Camera::center_.z + y,
              Camera::up_.x, Camera::up_.y, Camera::up_.z);
}


//////////////////////////////////////////
/// Private member functions
//////////////////////////////////////////

void
Camera::setMultiViewPort(void) const
{
    float w = this->win_.getWidth();
    float h = this->win_.getHeight();

    if (this->id_ == 1)
        glViewport(w/2, 0, w / 2, h);
    else
        glViewport(0, 0, w / 2, h);
}

}}
