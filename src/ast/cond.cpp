#include "cond.h"
#include "boolean.h"

namespace ploy { namespace AST
{

const Value* Cond::reduce(Environment* env) const
{
  for(auto branch : this->branches)
  {
    auto conditional = dynamic_cast<const Boolean*>(branch.first->reduce(env));
    if(!conditional || conditional->value)
    {
      return branch.second->reduce(env);
    }
  }

  return this->else_branch->reduce(env);
}

}}
