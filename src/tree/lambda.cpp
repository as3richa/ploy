#include "lambda.h"

namespace ploy
{

std::string Tree::Lambda::inspect(void)
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

std::string Tree::Lambda::description(void)
{
  return "lambda function";
}

}
