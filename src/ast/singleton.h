#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "value.h"

namespace ploy { namespace AST
{

class Singleton: public Value
{
private:
  std::string identifier;

public:
  Singleton(std::string identifier_) : identifier(identifier_) { ; }
  virtual std::string inspect(void) const;
};

}}

#endif
