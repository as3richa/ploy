#include "application.h"

#include <string>

#include <cassert>

namespace ploy
{

std::string Tree::Application::inspect(void) const
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

const Tree* Tree::Application::reduce(Environment* env) const
{
  auto fn = dynamic_cast<const Tree::Callable*>(this->fn->reduce(env));
  if(!fn)
  {
    assert(!"TODO");
    throw "TODO (not Callable)";
  }
  else
  {
    std::vector<const Tree*> reduced_params;
    for(auto& param : this->params)
    {
      reduced_params.push_back(param->reduce(env));
    }
    return fn->apply(reduced_params);
  }
}

}
