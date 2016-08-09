#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "../tree.h"

#include <gmpxx.h>

namespace ploy
{

class Tree::Number: public Value
{
private:
  mpq_class value;

public:
  Number(std::string lexeme);
  virtual std::string inspect(void);
  virtual std::string description(void);
};

}

#endif
