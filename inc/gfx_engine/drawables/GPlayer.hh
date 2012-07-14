//
// GPlayer.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 10:50:18 2011 arnaud mesureur
//

#ifndef	GPLAYER_HH_
#define GPLAYER_HH_

#include <GL/gl.h>
#include <GL/glu.h>

#include <Model.hpp>
#include <Clock.hpp>

#include "AElement.hh"
#include "APlayer.hh"
#include "IDrawable.hh"

namespace bomberman {
namespace gfx {

/**
 * The player.
 * @implements IDrawable
 */
class GPlayer : public IDrawable
{
public:
    /**
     * Constructor.
     * @param the element
     * @param the x position.
     * @param the y position.
     */
    GPlayer(AElement* e, float realX, float realY);

    /**
     * the draw implementation
     */
    void draw(void);

    /**
     * Reset the datas of the player.
     */
    void setData(AElement* e, float x, float y);

private:
    gdl::Model model_;
    AElement* GPlayer_;
    APlayer * APlayer_ ;
    float x_;
    float y_;
    float r_;

private:
    void update(void);
};

}}

#endif	// GPLAYER_HH_
