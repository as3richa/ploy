#include "or.h"
#include "boolean.h"

namespace ploy { namespace AST
{

const Value* Or::reduce(Environment* env) const
{
  if(params.size() == 0)
  {
    return Boolean::fromBool(false);
  }
  else
  {
    auto length = (int)params.size();
    for(int i = 0; i < length - 1; i ++)
    {
      auto param = params[i]->reduce(env);
      auto casted = dynamic_cast<const Boolean*>(param);
      if(!casted || casted->value == true)
      {
        return param;
      }
    }

    return params[length - 1]->reduce(env);
  }
}

}}
