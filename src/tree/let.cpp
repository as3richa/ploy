#include "let.h"

#include <memory>

#include "../environment.h"
#include "../tree.h"

namespace ploy
{

std::string Tree::Let::inspect(void) const
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

const Tree* Tree::Let::reduce(Environment* env) const
{
  auto new_env = env;
  for(auto& binding : this->bindings)
  {
    new_env = new Environment(binding.first, binding.second->reduce(env), new_env);
  }

  return this->body->reduce(new_env);
}

}
