/**
 * @file   String.hh
 * @author fares sabbagh <fares.sabbagh@epitech.eu>
 * @date   Wed Jun  1 18:20:58 2011
 *
 * @brief Draw Strings on the screen
 *
 */


#ifndef   	STRING_HH_
# define   	STRING_HH_

#include <Image.hpp>
#include <string>
#include <vector>
#include "Vector3f.hh"

namespace bomberman
{
  namespace gfx
  {
    class			String
    {
    public:
      static const float	gap = 32.0f;
      static const int		lbl = 16;

    private:
      std::vector<std::vector<Vector3f> > pos_;
      std::vector<std::string>	toPrint_;
      static gdl::Image		font_;
      std::string		order_;
      float			fontSize_;

    public:
      /**
       * Default constructor
       * @param text Text which will be print
       */
      String(const std::string &text = "", float size = 10);
      /**
       * Default constructor
       * @param nbr Number which will be print
       */
      String(unsigned int nbr, float size = 10);
      /**
       * Default destructor
       */
      ~String(void);
      /**
       * Get string at position 'idx' on the vector
       * @param idx position on the vector
       * @return string
       */
      const std::string	&getText(unsigned int idx = 0) const;
      /**
       * get the font size
       * @return font size
       */
      float	getFontSize(void) const;
      /**
       * Get the length of the string at the position 'idx' on the vector
       * @param idx position of the string
       * @return the length of the string
       */
      unsigned int	getLength(unsigned int idx = 0) const;
      /**
       * Get the number of strings on the vector
       * @return the number of strings
       */
      unsigned int	getNbrStrings(void) const;
      void		addText(const std::string &text);
      void		setText(const std::string &text, float size = 10);
      void		setText(const std::vector<std::string> &text, float size = 10);
      void		setFont(const std::string &filename);
      void		setFontSize(float size);

      void		printText(int posX, int posY, unsigned int idx);
      void		clear(void);

    private:
      void		fillVector(void);
      void		addVector(void);
    };
  }
}

#endif	    /* !STRING_HH_ */
