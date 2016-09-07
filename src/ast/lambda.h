#ifndef _LAMBDA_H_
#define _LAMBDA_H_

#include <vector>
#include <string>

#include "tree.h"

namespace ploy
{

class Tree::Lambda: public Tree
{
private:
  std::vector<std::string> identifiers;
  const Tree* body;

public:
  Lambda(std::vector<std::string> identifiers_, const Tree* body_) : identifiers(identifiers_), body(body_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
