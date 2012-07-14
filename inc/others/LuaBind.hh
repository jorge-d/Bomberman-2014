#ifndef LUABIND_HH_
# define LUABIND_HH_

# include <string>
# include <lua.hpp>

namespace lua
{
  class LuaBind
  {
  private:
    lua_State *lua_handle_;
    std::string file_;
  public:
    LuaBind(std::string const & file);
    LuaBind(void);
    ~LuaBind(void);
    LuaBind & operator=(LuaBind const & o);
    LuaBind & operator=(std::string const & file);
    void setFile(std::string const & file);
    std::string const & getFile() const;
    void load(void);
    void getGlobal(std::string const & global);
    void pushString(std::string const & string);
    void pushInteger(int nb);
    void pcall(int nargs, int nres, int errfunc);
    void pushStringTable(std::string *tab, int len);
    void pop(int nb);
    int toNumber(int index);
  };
}

#endif // LUABIND_HH_

