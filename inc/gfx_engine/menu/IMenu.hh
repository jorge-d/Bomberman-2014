//
// IMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:42:45 2011 fares sabbagh
//

#ifndef   	IMENU_HH_
# define   	IMENU_HH_

#include "GameEngine.hh"

namespace bomberman
{
  namespace gfx
  {
    class		IMenu
    {
    public:
      virtual	~IMenu(void) {}
      virtual void	initialize(bomberman::GameEngine *e) = 0;
      virtual void	draw(void) = 0;
      virtual void	update(void) = 0;
    };
  }
}

#endif	    /* !IMENU_HH_ */
