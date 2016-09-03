#ifndef _BOOLEAN_H_
#define _BOOLEAN_H_

#include "../tree.h"

#include <cassert>

namespace ploy
{

class Tree::Boolean: public Value
{
private:
  static const Boolean singletonFalse;
  static const Boolean singletonTrue;

public:
  const bool value;

  Boolean(bool value_) : value(value_) { ; }

  static const Boolean* fromValue(bool value);
  static const Boolean* fromLexeme(std::string lexeme);

  virtual std::string inspect(void) const;
};

}

#endif
