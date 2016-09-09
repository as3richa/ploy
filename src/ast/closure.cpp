#include "closure.h"

namespace ploy { namespace AST
{

std::string Closure::inspect(void) const
{
  return "#<lambda>";
}

const Value* Closure::apply(std::vector<const Value*> params) const
{
  if(params.size() != this->identifiers.size())
  {
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

}}
