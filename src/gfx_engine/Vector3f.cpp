//
// Vector3f.cpp for bomberman
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Fri May 20 19:35:02 2011 fares sabbagh
//

#include <iostream>
#include "Vector3f.hh"

namespace bomberman {
namespace gfx {

Vector3f::Vector3f(void)
    : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

}}
