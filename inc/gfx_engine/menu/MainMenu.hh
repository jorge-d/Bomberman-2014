//
// MainMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	MAINMENU_HH_
# define   	MAINMENU_HH_

#include <Image.hpp>

#include "IMenu.hh"
#include "Menu.hh"
#include "GameEngine.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		MainMenu : public Menu, public IMenu
    {
    public:
      MainMenu(void);
      ~MainMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    private:
      void		drawBackground(void);
    };
  }
}

#endif	    /* !MAINMENU_HH_ */
