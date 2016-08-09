#ifndef _CONS_H_
#define _CONS_H_

#include <string>
#include <memory>

#include "../tree.h"

namespace ploy
{

class Tree::Cons: public Tree
{
private:
  TreePointer first;
  TreePointer rest;

public:
  Cons(TreePointer first_, TreePointer rest_) : first(first_), rest(rest_) { ; }
  virtual std::string inspect(void);
  virtual bool reducibile(void);
  virtual TreePointer reduce(void);
};

}

#endif
