#include "application.h"

#include <string>

namespace ploy
{

std::string Tree::Application::inspect(void)
{
  std::string result = "(";
  result += this->fn->inspect();
  for(auto& param : this->params)
  {
    result += ' ';
    result += param->inspect();
  }
  result += ')';
  return result;
}

bool Tree::Application::reducibile(void)
{
  if(this->fn->reducibile())
    return true;

  for(auto& param : this->params)
    if(param->reducibile())
      return true;

  return false;
}

TreePointer Tree::Application::reduce(void)
{
  throw "TODO";
}

}
