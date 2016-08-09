#include "or.h"

#include <string>

namespace ploy
{

std::string Tree::Or::inspect(void)
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

bool Tree::Or::reducibile(void)
{
  for(auto& param : this->params)
    if(param->reducibile())
      return true;

  return false;
}

TreePointer Tree::Or::reduce(void)
{
  throw "TODO";
}

std::string Tree::Or::description(void)
{
  return std::string("Or expression");
}

}
