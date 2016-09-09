#include "builtin_function.h"

namespace ploy { namespace AST
{

std::string BuiltinFunction::inspect(void) const
{
  return std::string("#<builtin procedure ") + this->identifier + ">";
}

const Value* BuiltinFunction::apply(std::vector<const Value*> params) const
{
  auto count = (int)params.size();
  if(!(this->min_arity <= count && count <= this->max_arity))
  {
    throw "TODO";
  }

  return this->callback(params);
}

}}
