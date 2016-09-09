#include "cons.h"

namespace ploy { namespace AST
{

std::string Cons::inspect(void) const
{
  std::string result = "(cons ";
  result += this->first->inspect();
  result += ' ';
  result += this->rest->inspect();
  result += ')';
  return result;
}

}}
