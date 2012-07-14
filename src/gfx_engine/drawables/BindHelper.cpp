//
// BindHelper.hh for bomberman
//
// Made by arnaud mesureur
// Login   <mesure_a@epitech.net>
//
// Started on  Sun May 29 06:51:07 2011 arnaud mesureur
//

#include <iostream>

#include <gdl/Image.hpp>

#include "BindHelper.hh"

namespace bomberman {
namespace gfx {

bindable_type BindHelper::currentBind_ = NONE;

void
BindHelper::bind(gdl::Image& img, bindable_type btype)
{
    if (BindHelper::currentBind_ != btype)
    {
      img.bind();
      BindHelper::currentBind_ = btype;
    }
}

void
BindHelper::reset(void)
{
    BindHelper::currentBind_ = NONE;
}

}}
