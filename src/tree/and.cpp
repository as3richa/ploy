#include "and.h"

#include <string>

namespace ploy
{

std::string Tree::And::inspect(void)
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

bool Tree::And::reducibile(void)
{
  for(auto& param : this->params)
    if(param->reducibile())
      return true;

  return false;
}

TreePointer Tree::And::reduce(void)
{
  throw "TODO";
}

}
