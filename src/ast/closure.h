#ifndef _AST_CLOSURE_H_
#define _AST_CLOSURE_H_

#include <vector>
#include "callable.h"

namespace ploy { namespace AST
{

class Closure: public Callable
{
private:
  std::vector<std::string> identifiers;
  const Node* body;
  Environment* env;

public:
  Closure(std::vector<std::string> identifiers_, const Node* body_, Environment* env_) :
    identifiers(identifiers_), body(body_), env(env_) { ; }
  virtual std::string inspect(void) const;
  virtual const Value* apply(std::vector<const Value*>) const;
};

}}

#endif
