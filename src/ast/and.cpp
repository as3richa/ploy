#include "and.h"
#include "boolean.h"

namespace ploy { namespace AST
{

const Value* And::reduce(Environment* env) const
{
  if(params.size() == 0)
  {
    return Boolean::fromBool(true);
  }
  else
  {
    auto length = (int)params.size();
    for(int i = 0; i < length - 1; i ++)
    {
      auto casted = dynamic_cast<const Boolean*>(params[i]->reduce(env));
      if(casted && casted->value == false)
      {
        return Boolean::fromBool(false);
      }
    }

    return params[length - 1]->reduce(env);
  }
}

}}
