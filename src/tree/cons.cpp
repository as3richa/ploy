#include "cons.h"

namespace ploy
{

std::string Tree::Cons::inspect(void)
{
  std::string result = "(cons ";
  result += this->first->inspect();
  result += ' ';
  result += this->rest->inspect();
  result += ')';
  return result;
}

bool Tree::Cons::reducibile(void)
{
  return this->first->reducibile() || this->rest->reducibile();
}

TreePointer Tree::Cons::reduce(void)
{
  throw "TODO";
}

}
