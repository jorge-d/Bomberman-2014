#ifndef TEXT_HPP
# define TEXT_HPP

# include <string>
# include "Color.hpp"

namespace gdl
{
  class TextImpl;

  class	Text
  {
  public:
    Text(std::string const &);

    void		setText(std::string const &);
    void		setFont(std::string const &);
    void		setColor(gdl::Color const &);
    void		setPosition(unsigned int const, unsigned int const);
  private:
    Text(void);
    gdl::TextImpl	textImpl_;
  };
}

#endif /* !TEXT_HPP */
