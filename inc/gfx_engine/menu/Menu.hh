//
// Menu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Wed May 25 21:48:01 2011 fares sabbagh
//


#ifndef   	MENU_HH_
# define   	MENU_HH_

#include <iostream>
#include <Image.hpp>
#include <Window.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <map>
#include <string>

#include "GameEngine.hh"
#include "String.hh"
#include "IMenu.hh"

namespace bomberman
{
  namespace gfx
  {
    class	Menu
    {
    private:
      std::map<enum bomberman::menu, IMenu * > menu_;

    protected:
      static const int	gap = 50;
      unsigned int	nElemH;
      static gdl::Image	arrow_;
      int		trX;
      Vector3f		pos_;

      bomberman::GameEngine *gameEngine_;
      bomberman::menu mode_;
      gdl::Image background_;
      gfx::String gfxString_;
      unsigned int	from_;
      unsigned int	cursor_;

    public:
      Menu();
      ~Menu(void);
      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    protected:
      void		setBackground(const char *filename);
      virtual void	drawZone(void);
      virtual void	drawText(void);
      virtual void	drawArrow(void);
    };
  }
}

#endif	    /* !MENU_HH_ */
