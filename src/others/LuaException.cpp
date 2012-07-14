#include "LuaException.hh"

lua::LuaException::LuaException() throw()
{}

lua::LuaException::LuaException(std::string const & what) throw()
{
  this->what_ = what;
}

lua::LuaException::~LuaException() throw()
{}

const char * lua::LuaException::what(void) const throw()
{
  return this->what_.c_str();
}
