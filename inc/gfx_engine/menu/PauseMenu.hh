//
// PauseMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	PAUSEMENU_HH_
# define   	PAUSEMENU_HH_

#include <Image.hpp>

#include "IMenu.hh"
#include "Menu.hh"
#include "GameEngine.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		PauseMenu : public Menu, public IMenu
    {
    private:
      bool		drawBack_;

    public:
      PauseMenu(void);
      ~PauseMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    public:
      void		reset(bool);

    private:
      void		drawBackground(void);
      virtual void	drawZone(void);
    };
  }
}

#endif	    /* !PAUSEMENU_HH_ */
