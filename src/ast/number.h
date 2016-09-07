#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "tree.h"

#include <gmpxx.h>

namespace ploy
{

class Tree::Number: public Value
{
private:
  static mpq_class parse(std::string lexeme);

public:
  const mpq_class value;
  Number(std::string lexeme) : value(parse(lexeme)) { ; };
  Number(mpq_class value_) : value(value_) { ; };
  virtual std::string inspect(void) const;
  virtual bool eq(const Tree* other) const;
};

}

#endif
