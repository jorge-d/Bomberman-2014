//
// LoadMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	LOADMENU_HH_
# define   	LOADMENU_HH_

#include <Image.hpp>

#include "IMenu.hh"
#include "Menu.hh"
#include "GameEngine.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		LoadMenu : public Menu, public IMenu
    {
    public:
      LoadMenu(void);
      ~LoadMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    private:
      void		loadText(void);
      void		drawBackground(void);
    };
  }
}

#endif	    /* !LOADMENU_HH_ */
