#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "tree.h"

#include <string>

namespace ploy
{

class Tree::Singleton: public Tree::Value
{
private:
  std::string identifier;

public:
  Singleton(std::string identifier_) : identifier(identifier_) { ; }
  virtual std::string inspect(void) const;
};

}

#endif
