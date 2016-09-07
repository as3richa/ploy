#ifndef _CONS_H_
#define _CONS_H_

#include <string>
#include <memory>

#include "tree.h"

namespace ploy
{

class Tree::Cons: public Tree
{
public:
  const Tree* const first;
  const Tree* const rest;

  Cons(const Tree* first_, const Tree* rest_) : first(first_), rest(rest_) { ; }
  virtual std::string inspect(void) const;
  virtual bool reducibile(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
