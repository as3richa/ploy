#include "closure.h"

#include "../environment.h"
#include "tree.h"

namespace ploy
{

std::string Tree::Closure::inspect(void) const
{
  std::string result = "(lambda (";
  for(auto& id : this->identifiers)
  {
    result += id;
    result += ' ';
  }
  result[result.size() - 1] = ')';
  result += ' ';
  result += this->body->inspect();
  result += ')';
  return result;
}

const Tree* Tree::Closure::apply(std::vector<const Tree*> params) const
{
  if(params.size() != this->identifiers.size())
  {
    assert(!"TODO");
    throw "TODO";
  }
  else
  {
    auto env = this->env;

    int length = params.size();
    for(int i = 0; i < length; i ++)
    {
      env = new Environment(this->identifiers[i], params[i], env);
    }

    return this->body->reduce(env);
  }
}

}
