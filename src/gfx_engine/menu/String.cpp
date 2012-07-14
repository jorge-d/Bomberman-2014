//
// String.cpp for  in /home/sabbag_a/test/bomberman-2014-rodrig_d/examples/tuto
//
// Made by fares sabbagh
// Login   <sabbag_a@epitech.net>
//
// Started on  Mon May 23 04:30.05:52 2011 fares sabbagh

//

#include <iostream>
#include <algorithm>
#include <Image.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <sstream>
#include <vector>
#include <string>

#include "BindHelper.hh"
#include "LoadHelper.hpp"
#include "String.hh"

namespace bomberman
{
  namespace gfx
  {
    gdl::Image	String::font_ = loadHelper<gdl::Image>("./assets/menu/text.png");

    String::String(const std::string &text, float size) :
      order_(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")
    {
      if (text.length() != 0)
	this->toPrint_.push_back(text);
      this->fillVector();
      this->fontSize_ = size;
    }

    String::String(unsigned int nbr, float size) :
      order_(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~")
    {
      std::ostringstream oss;
      std::string text;

      oss << nbr;
      text = oss.str();
      if (text.length() != 0)
	this->toPrint_.push_back(text);
      this->fillVector();
      this->fontSize_ = size;
    }

    String::~String(void)
    {
    }

    void
    String::clear(void)
    {
      this->toPrint_.clear();
      this->pos_.clear();
    }

    void
    String::setFont(const std::string &filename)
    {
      this->font_ = gdl::Image::load(filename);
    }

    const std::string&
    String::getText(unsigned int idx) const
    {
      return this->toPrint_.at(idx);
    }

    float
    String::getFontSize(void) const
    {
      return this->fontSize_;
    }

    unsigned int
    String::getNbrStrings(void) const
    {
      return this->toPrint_.size();
    }

    unsigned int
    String::getLength(unsigned int idx) const
    {
      return this->toPrint_.at(idx).length();
    }

    void
    String::setText(const std::string &text, float size)
    {
      this->toPrint_.clear();
      this->pos_.clear();
      this->toPrint_.push_back(text);
      this->fontSize_ = size;
      this->fillVector();
    }

    void
    String::setFontSize(float size)
    {
      this->fontSize_ = size;
    }

    void
    String::setText(const std::vector<std::string> &text, float size)
    {
      this->toPrint_.clear();
      this->pos_.clear();
      this->toPrint_.resize(text.size());
      copy(text.begin(), text.end(), this->toPrint_.begin());
      this->fontSize_ = size;
      this->fillVector();
    }

    void
    String::addText(const std::string &text)
    {
      this->toPrint_.push_back(text);
      this->addVector();
    }

    void
    String::addVector(void)
    {
      float	x;
      float	y;
      int	i;
      int	idx;
      int	len;

      len = this->toPrint_.at(this->toPrint_.size() - 1).length();
      std::vector<Vector3f> tmp;
      for (i = 0; i < len; i++)
      {
	idx = this->order_.find(this->toPrint_.at(this->toPrint_.size() - 1).at(i));
	x = (idx % gfx::String::lbl) * gfx::String::gap + (gfx::String::gap / 4.5f);
	y = ceil(idx / gfx::String::lbl) * gfx::String::gap;
	tmp.push_back(Vector3f(x / this->font_.getWidth(), y / this->font_.getHeight(), 0));
      }
      this->pos_.push_back(tmp);
    }

    void
    String::fillVector(void)
    {
      float	x;
      float	y;
      int	i;
      int	idx;
      int	len;

      std::vector<std::string>::iterator it = this->toPrint_.begin();

      for (; it != this->toPrint_.end(); ++it)
      {
	len = (*it).length();
	std::vector<Vector3f> tmp;
	for (i = 0; i < len; i++)
	{
	  idx = this->order_.find((*it).at(i));
	  x = (idx % gfx::String::lbl) * gfx::String::gap + (gfx::String::gap / 4.5f);
	  y = ceil(idx / gfx::String::lbl) * gfx::String::gap;
	  tmp.push_back(Vector3f(x / this->font_.getWidth(), y / this->font_.getHeight(), 0));
	}
	this->pos_.push_back(tmp);
      }
    }

    void
    String::printText(int posX, int posY, unsigned int idx)
    {
      glEnable(GL_TEXTURE_2D);
      glEnable(GL_BLEND);

      if (this->pos_.size() <= idx)
	return ;
      std::vector<Vector3f>::iterator it = this->pos_.at(idx).begin();
      BindHelper::bind(this->font_, FONT_TEXT);
      glPushMatrix();
      glTranslatef(posX, posY, 0);
      glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
      glAlphaFunc(GL_GREATER, 1);
      for (; it != pos_.at(idx).end(); ++it)
      {
	glTranslatef(this->fontSize_ + 10, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(it->x, it->y);
	glVertex2f(-this->fontSize_, this->fontSize_);
	glTexCoord2f(it->x, it->y + (gfx::String::gap / this->font_.getHeight()));
	glVertex2f(-this->fontSize_, -this->fontSize_);
	glTexCoord2f(it->x + (20.0f / this->font_.getWidth()), it->y + (gfx::String::gap / this->font_.getHeight()));
	glVertex2f(this->fontSize_, -this->fontSize_);
	glTexCoord2f(it->x +  (20.0f / this->font_.getWidth()), it->y);
	glVertex2f(this->fontSize_, this->fontSize_);
	glEnd();
      }
      glPopMatrix();
      glDisable(GL_BLEND);
      glDisable(GL_TEXTURE_2D);
    }
  }
}
