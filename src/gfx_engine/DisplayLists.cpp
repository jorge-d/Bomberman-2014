//
// DisplayLists.cpp for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <queue>
#include <map>

#include "DisplayLists.hh"
#include "IPrimitive.hh"

namespace bomberman {
namespace gfx {

//////////////////////////////////////////
/// Singleton Constructor / Destructor
//////////////////////////////////////////

DisplayLists* DisplayLists::instance_ = NULL;

DisplayLists::DisplayLists(void)
{
}

DisplayLists::~DisplayLists(void)
{
    this->instance_ = NULL;
}

//////////////////////////////////////////
/// Public member functions
//////////////////////////////////////////

DisplayLists&
DisplayLists::getInstance(void)
{
    if (DisplayLists::instance_ == NULL)
        return (*(DisplayLists::instance_ = new DisplayLists));
    else
        return *DisplayLists::instance_;
}

void
DisplayLists::destroyInstance(void)
{
    delete DisplayLists::instance_;
}

void
DisplayLists::createList(display_id id, IPrimitive* p)
{
    this->addToList(p);
    this->handles_[id] = this->genList();
}

void
DisplayLists::call(display_id id) const
{
    std::map<display_id, GLuint>::const_iterator it =
        this->handles_.find(id);

    if (it != this->handles_.end())
    {
      glEnable(GL_TEXTURE_2D);
      glDisable(GL_BLEND);
      glCallList(it->second);
      glDisable(GL_TEXTURE_2D);
    }
    else
      std::cerr << "DisplayLists: error: list id not found" << std::endl;
}

void
DisplayLists::operator[](display_id id) const
{
    this->call(id);
}


//////////////////////////////////////////
/// Private member functions
//////////////////////////////////////////

void
DisplayLists::addToList(IPrimitive* p)
{
    if (p != NULL)
    {
        this->list_.push(p);
    }
}

GLuint
DisplayLists::genList(void)
{
    if (this->list_.empty() == false)
    {
        GLuint id = glGenLists(this->list_.size());

        while (!this->list_.empty())
        {
            IPrimitive* p = this->list_.front();
            this->list_.pop();

            glNewList(id, GL_COMPILE);
            p->compute();
            glEndList();
            delete p;
        }
        return id;
    }
    std::cerr << "Error: display lists are empty" << std::endl;
    return 0;
}

}}
