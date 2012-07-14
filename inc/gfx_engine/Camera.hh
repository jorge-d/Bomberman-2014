//
// Camera.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sat May 21 04:18:25 2011 arnaud mesureur
//

#ifndef CAMERA_HH_
#define CAMERA_HH_

#include "gdl/Window.hpp"

#include "Vector3f.hh"

namespace bomberman {
namespace gfx {

/**
 * The camera.
 * A camera is linked to a screenboard and a player
 * by a single id. There are as many cameras as players.
 *
 * @see gdl::Window
 */
class Camera
{
//////////////////////////////////////////
/// Public members
//////////////////////////////////////////
public:
    /**
     * Constructor.
     * @param the player/screenboard id.
     */
    Camera(int id = 0);

public:
    /**
     * Initialize the camera, depending on the id and the number of
     * human players.
     */
    void initialize(void) const;
    /**
     * Update the camera position.
     * @param the x position.
     * @param the y position.
     */
    void update(float x, float y) const;

//////////////////////////////////////////
/// Private members
//////////////////////////////////////////
private:
    /// constant values
    static const float fovy_;
    static const float zNear_;
    static const float zFar_;
    static const Vector3f eye_;
    static const Vector3f center_;
    static const Vector3f up_;

private:
    gdl::Window win_;
    int id_;

private:
    void setMultiViewPort(void) const;
};

}}

#endif	// CAMERA_HH_
