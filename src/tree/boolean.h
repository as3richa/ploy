#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_

#include "../tree.h"

#include <cassert>

namespace ploy
{

class Tree::Boolean: public Value
{
private:
  bool value;

public:
  Boolean(std::string lexeme)
  {
    assert(lexeme == "#t" || lexeme == "#f");
    value = (lexeme == "#t");
  }

  virtual std::string inspect(void);
};

}

#endif
