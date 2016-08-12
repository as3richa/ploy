#include "cond.h"

#include "../tree.h"

namespace ploy
{

std::string Tree::Cond::inspect(void) const
{
  throw "TODO";
}

const Tree* Tree::Cond::reduce(Environment* env) const
{
  for(auto branch : this->branches)
  {
    auto conditional = dynamic_cast<const Tree::Boolean*>(branch.first->reduce(env));
    if(!conditional || conditional->value)
    {
      return branch.second->reduce(env);
    }
  }

  return this->else_branch->reduce(env);
}

}
