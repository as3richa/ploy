#include "builtin_function.h"

#include "../environment.h"
#include "tree.h"

namespace ploy
{

std::string Tree::BuiltinFunction::inspect(void) const
{
  return std::string("#<builtin procedure ") + this->identifier + ">";
}

const Tree* Tree::BuiltinFunction::apply(std::vector<const Tree*> params) const
{
  auto count = (int)params.size();
  if(!(this->min_arity <= count && count <= this->max_arity))
  {
    throw "TODO";
  }

  return this->callback(params);
}

}
