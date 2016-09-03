#include "and.h"

#include <string>

namespace ploy
{

std::string Tree::And::inspect(void) const
{
  std::string result = "(and";
  for(auto& param : this->params)
  {
    result += ' ';
    result += param->inspect();
  }
  result += ')';
  return result;
}

const Tree* Tree::And::reduce(Environment* env) const
{
  if(params.size() == 0)
  {
    return Tree::Boolean::fromValue(true);
  }
  else
  {
    auto length = (int)params.size();
    for(int i = 0; i < length - 1; i ++)
    {
      auto param = params[i]->reduce(env);
      auto casted = dynamic_cast<const Tree::Boolean*>(param);

      if(casted && casted->value == false)
      {
        return Tree::Boolean::fromValue(false);
      }
    }

    return params[length - 1]->reduce(env);
  }
}

}
