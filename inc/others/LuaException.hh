#ifndef LUAEXCEPTION_HH_
# define LUAEXCEPTION_HH_

# include <string>
# include <exception>

namespace lua
{
  class LuaException : public std::exception
  {
  private:
    std::string what_;
  public:
    LuaException() throw();
    LuaException(std::string const & what) throw();
    ~LuaException() throw();
    const char * what(void) const throw();
  };
}

#endif // LUAEXCEPTION_HH_
