#ifndef _DEFINITION_H_
#define _DEFINITION_H_

#include "tree.h"

namespace ploy
{

class Tree::Definition: public Tree
{
private:
  std::string identifier;
  const Tree* body;

public:
  Definition(std::string identifier_, const Tree* body_) : identifier(identifier_), body(body_) { ; }
  virtual const Tree* reduce(Environment*) const;
  virtual std::string inspect(void) const;
};

}

#endif
