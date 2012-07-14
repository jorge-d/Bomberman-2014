#include "LuaException.hh"
#include "LuaBind.hh"

lua::LuaBind::LuaBind(std::string const & file)
  : lua_handle_(NULL), file_(file)
{}

lua::LuaBind::LuaBind(void)
  : lua_handle_(NULL), file_("")
{}

lua::LuaBind::~LuaBind(void)
{
  if (this->lua_handle_)
    lua_close(this->lua_handle_);
}

lua::LuaBind & lua::LuaBind::operator=(lua::LuaBind const & o)
{
  this->file_ = o.getFile();
  return *this;
}

lua::LuaBind & lua::LuaBind::operator=(std::string const & file)
{
  this->setFile(file);
  return *this;
}

void lua::LuaBind::setFile(std::string const & file)
{
  this->file_ = file;
}

std::string const & lua::LuaBind::getFile() const
{
  return this->file_;
}

void lua::LuaBind::load(void)
{
  if ((this->lua_handle_ = lua_open()) == NULL)
    throw lua::LuaException("Cannot open lua.");
  luaL_openlibs(this->lua_handle_);
  if (luaL_loadfile(this->lua_handle_, this->file_.c_str()) == -1)
    throw lua::LuaException(lua_tostring(this->lua_handle_, -1));
  if (lua_pcall(this->lua_handle_, 0, 0, 0) != 0)
    throw lua::LuaException(lua_tostring(this->lua_handle_, -1));
}

void lua::LuaBind::getGlobal(std::string const & global)
{
  lua_getglobal(this->lua_handle_, global.c_str());
}

void lua::LuaBind::pushString(std::string const & string)
{
  lua_pushstring(this->lua_handle_, string.c_str());
}

void lua::LuaBind::pushInteger(int nb)
{
  lua_pushinteger(this->lua_handle_, nb);
}

void lua::LuaBind::pcall(int nargs, int nres, int errfunc)
{
  if (lua_pcall(this->lua_handle_, nargs, nres, errfunc) != 0)
    throw lua::LuaException(lua_tostring(this->lua_handle_, -1));
}

#include <iostream>

void lua::LuaBind::pushStringTable(std::string *tab, int len)
{
  lua_newtable(this->lua_handle_);
  for (int i =0; i < len; ++i)
    {
      lua_pushinteger(this->lua_handle_, i + 1);
      lua_pushstring(this->lua_handle_, tab[i].c_str());
      lua_settable(this->lua_handle_, -3);
    }
}

int lua::LuaBind::toNumber(int index)
{
  return lua_tonumber(this->lua_handle_, index);
}

void lua::LuaBind::pop(int nb)
{
  lua_pop(this->lua_handle_, nb);
}
