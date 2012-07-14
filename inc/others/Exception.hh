#ifndef __BOMB_EXCEPTIONS_H__
# define __BOMB_EXCEPTIONS_H__

#include <string>
#include <iostream>
#include <exception>

namespace bomberman {

class Exception : public std::exception
{
private:
  std::string p_msg;

public:
  Exception(const char *) throw();
  ~Exception() throw();
  const char *what() const throw();
};

}

#endif
