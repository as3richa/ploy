#include "cons.h"

namespace ploy
{

std::string Tree::Cons::inspect(void) const
{
  std::string result = "(cons ";
  result += this->first->inspect();
  result += ' ';
  result += this->rest->inspect();
  result += ')';
  return result;
}

bool Tree::Cons::reducibile(void) const
{
  return this->first->reducibile() || this->rest->reducibile();
}

const Tree* Tree::Cons::reduce(Environment* env) const
{
  (void)env;
  throw "TODO";
}

}
