//
// IntroSceneMenu.hh for bomberman in /projects/
//
// Made by fares sabbagh
// Login  sabbag_a <fares.sabbagh@epitech.eu>
//
// Started on  Fri May 27 18:50:41 2011 fares sabbagh
//


#ifndef   	INTROSCENEMENU_HH_
# define   	INTROSCENEMENU_HH_

#include <Model.hpp>

#include "Menu.hh"
#include "IMenu.hh"
#include "GameEngine.hh"
#include "DisplayLists.hh"
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class		IntroSceneMenu : public Menu, public IMenu
    {
    public:
      IntroSceneMenu(void);
      ~IntroSceneMenu(void);

      virtual void	initialize(bomberman::GameEngine *e);
      virtual void	draw(void);
      virtual void	update(void);

    private:
      void		drawMarvin(void);
      void		drawBomb(void);
      void		drawBackground(void);

    private:
      Vector3f		rotB_;
      gdl::Model	marvin_;
      gdl::Model	bomb_;
      DisplayLists&	dlists_;
    };
  }
}

#endif	    /* !INTROSCENEMENU_HH_ */
