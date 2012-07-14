//
// EndMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	WINMENU_HH_
# define   	WINMENU_HH_

#include <Image.hpp>
#include "String.hh"
#include "IMenu.hh"
#include "Menu.hh"
#include "GameEngine.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		WinMenu : public Menu, public IMenu
    {
    private:
      gfx::String	introString_;
      bomberman::menu	lastWinner_;

    public:
      WinMenu(void);
      ~WinMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    private:
      void		drawBackground(void);
      virtual void	drawText(void);
    };
  }
}

#endif	    /* !WINMENU_HH_ */
