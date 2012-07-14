//
// Square.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Mon May 23 03:31:59 2011 arnaud mesureur
//

#include <cstdlib>

#include "Human.hh"
#include "ScreenBoard.hh"
#include "Square.hh"
#include "APlayer.hh"
#include "GPlayer.hh"
#include "Map.hh"
#include "GEmpty.hh"

namespace bomberman {
namespace gfx {

const unsigned Square::size = 350;
std::map<int, GPlayer*> Square::stock_;

//////////////////////////////////////////
/// Constructor / Destructor
//////////////////////////////////////////

Square::Square(int parentId, Map* map, unsigned int x, unsigned int y)
    : parentId_(parentId),
      map_(map), mapX_(x), mapY_(y),
      object_(NULL)
{
    this->realX_ = x * Square::size;
    this->realY_ = y * Square::size;
    this->map_->recoverPlayerAt(this->players_, this->mapX_, this->mapY_);
    this->object_ = this->map_->recoverObjectAt(this->mapX_, this->mapY_);
    this->load();
}

Square::~Square(void)
{
}

//////////////////////////////////////////
/// Public member functions
//////////////////////////////////////////

void
Square::draw(void)
{
    //////////////////////////////////////////
    /// Draw items
    //////////////////////////////////////////
    for (std::list<gfx::IDrawable*>::iterator it = this->gfxContent_.begin();
         it != this->gfxContent_.end(); ++it)
    {
        (*it)->draw();
        delete *it;
    }

    //////////////////////////////////////////
    /// Draw players
    //////////////////////////////////////////
    for (std::list<gfx::GPlayer*>::iterator it = this->gfxPlayers_.begin();
         it != this->gfxPlayers_.end(); ++it)
        (*it)->draw();
    this->gfxPlayers_.clear();
}

void
Square::unload(void)
{
    std::map<int, GPlayer*>::iterator it = Square::stock_.begin();
    for (; it != Square::stock_.end(); ++it)
        delete (*it).second;
    Square::stock_.clear();
}

//////////////////////////////////////////
/// Private member functions
//////////////////////////////////////////
void
Square::load(void)
{
    this->gfxContent_.push_back(new GEmpty(this->realX_, this->realY_));
    if (this->object_)
    {
        IDrawable* elem = this->factory_.build(this->object_->getType(),
                                               this->object_,
                                               this->realX_, this->realY_);
        if (elem != NULL)
            this->gfxContent_.push_back(elem);
    }
    if (!this->players_.empty())
    {
        std::list<APlayer*>::iterator it = this->players_.begin();
        for (; it != this->players_.end(); ++it)
        {
            GPlayer* player = NULL;
            std::map<int, GPlayer*>::iterator res = this->stock_.find((*it)->getID());
            if (res != this->stock_.end())
            {
                player = (*res).second;
                player->setData(*it,
                                (*it)->getRealPosX() * Square::size,
                                (*it)->getRealPosY() * Square::size);
            }
            else
            {
                player = dynamic_cast<GPlayer*>(this->factory_.build((*it)->getType(), *it,
                                                                     (*it)->getRealPosX() * Square::size,
                                                                     (*it)->getRealPosY() * Square::size));
                if (player != NULL)
                    this->stock_[(*it)->getID()] = player;
            }
            if (player != NULL)
                this->gfxPlayers_.push_back(player);
        }
    }
}

}}
