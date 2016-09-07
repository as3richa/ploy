#include "definition.h"

#include "../environment.h"

namespace ploy
{

std::string Tree::Definition::inspect(void) const
{
  return std::string("(define ") + this->identifier + " " + this->body->inspect() + ")";
}

const Tree* Tree::Definition::reduce(Environment* env) const
{
  env->mutate(this->identifier, this->body->reduce(env));
  return nullptr;
}

}
