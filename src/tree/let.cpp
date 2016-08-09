#include "let.h"

#include <memory>

#include "../tree.h"

namespace ploy
{

std::string Tree::Let::inspect(void)
{
  std::string result = "(let (";
  for(auto& binding : this->bindings)
  {
    result += '[';
    result += binding.first;
    result += ' ';
    result += binding.second->inspect();
    result += ']';
    result += ' ';
  }
  result[result.size() - 1] = ')';
  result += ' ';
  result += this->body->inspect();
  result += ')';
  return result;
}

bool Tree::Let::reducibile(void)
{
  return true;
}

TreePointer Tree::Let::reduce(void)
{
  throw "TODO";
}

}
