#include "lambda.h"

#include <vector>

namespace ploy
{

std::string Tree::Lambda::inspect(void) const
{
  std::string result = "(lambda (";
  for(auto& id : this->identifiers)
  {
    result += id;
    result += ' ';
  }
  result[result.size() - 1] = ')';
  result += ' ';
  result += this->body->inspect();
  result += ')';
  return result;
}

const Tree* Tree::Lambda::reduce(Environment* env) const
{
  return new Tree::Closure(this->identifiers, this->body, env);
}

}
