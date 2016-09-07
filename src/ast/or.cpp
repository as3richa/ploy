#include "or.h"

#include <string>

namespace ploy
{

std::string Tree::Or::inspect(void) const
{
  std::string result = "(or";
  for(auto& param : this->params)
  {
    result += ' ';
    result += param->inspect();
  }
  result += ')';
  return result;
}

const Tree* Tree::Or::reduce(Environment* env) const
{
  if(params.size() == 0)
  {
    return Tree::Boolean::fromValue(false);
  }
  else
  {
    auto length = (int)params.size();
    for(int i = 0; i < length - 1; i ++)
    {
      auto param = params[i]->reduce(env);
      auto casted = dynamic_cast<const Tree::Boolean*>(param);

      if(!casted || casted->value == true)
      {
        return param;
      }
    }

    return params[length - 1]->reduce(env);
  }
}

}
