#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_

#include "../tree.h"

#include <cassert>

namespace ploy
{

class Tree::Boolean: public Value
{
public:
  const bool value;

  Boolean(bool value_) : value(value_) { ; }
  Boolean(std::string lexeme) : value(lexeme == "#t")
  {
    assert(lexeme == "#t" || lexeme == "#f");
  }

  virtual std::string inspect(void) const;
};

}

#endif
