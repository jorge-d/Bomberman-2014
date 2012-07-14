//
// Vector3f.hh for bomberman in /home/sabbag_a/bomberman-2014-rodrig_d/inc/gfx_engine
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Fri May 20 18:55:38 2011 fares sabbagh
//

#ifndef   	VECTOR3F_HH_
#define   	VECTOR3F_HH_

namespace bomberman {
namespace gfx {

/**
 * A vector "3 float".
 * A 3-element vector that is represented by single-precision
 * floating point x,y,z coordinates
 */
struct Vector3f
{
    float x;
    float y;
    float z;
    Vector3f(void);
    Vector3f(float x, float y, float z);
};

}}

#endif	    /* !VECTOR3F_HH_ */
