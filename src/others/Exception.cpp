#include "Exception.hh"

namespace bomberman {

Exception::Exception(const char * msg) throw()
{
  this->p_msg = msg;
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
  return this->p_msg.c_str();
}

}
