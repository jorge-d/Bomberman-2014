//
// NewGameMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	SCOREMENU_HH_
# define   	SCOREMENU_HH_

#include <Image.hpp>

#include "IMenu.hh"
#include "Menu.hh"
#include "GameEngine.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		ScoreMenu : public Menu, public IMenu
    {
    private:
      std::string	indent_;
      gfx::String	board_;

    public:
      ScoreMenu(void);
      ~ScoreMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    private:
      void		drawBackground(void);
      virtual void	drawZone(void);
      virtual void	drawText(void);
      void		loadText(void);
    };
  }
}

#endif	    /* !SCOREMENU_HH_ */
