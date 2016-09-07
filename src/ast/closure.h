#ifndef _CLOSURE_H_
#define _CLOSURE_H_

#include "lambda.h"

#include "tree.h"

namespace ploy
{

class Tree::Closure: public Tree::Callable
{
private:
  std::vector<std::string> identifiers;
  const Tree* body;
  Environment* env;

public:
  Closure(std::vector<std::string> identifiers_, const Tree* body_, Environment* env_) :
    identifiers(identifiers_), body(body_), env(env_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* apply(std::vector<const Tree*>) const;
};

}

#endif
