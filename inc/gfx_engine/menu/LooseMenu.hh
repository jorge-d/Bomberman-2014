//
// EndMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	LOOSEMENU_HH_
# define   	LOOSEMENU_HH_

#include <Image.hpp>

#include "IMenu.hh"
#include "Menu.hh"
#include "GameEngine.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		LooseMenu : public Menu, public IMenu
    {
    public:
      LooseMenu(void);
      ~LooseMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    private:
      void		drawBackground(void);
    };
  }
}

#endif	    /* !LOOSEMENU_HH_ */
