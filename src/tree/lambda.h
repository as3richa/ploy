#ifndef _LAMBDA_H_
#define _LAMBDA_H_

#include <list>
#include <string>

#include "../tree.h"

namespace ploy
{

class Tree::Lambda: public Value
{
private:
  std::list<std::string> identifiers;
  TreePointer body;

public:
  Lambda(std::list<std::string> identifiers_, TreePointer body_) : identifiers(identifiers_), body(body_) { ; }
  virtual std::string inspect(void);
  virtual std::string description(void);
};

}

#endif
