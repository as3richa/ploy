#include "identifier.h"

#include <string>

#include "../tree.h"

namespace ploy
{

std::string Tree::Identifier::inspect(void)
{
  return this->lexeme;
}

bool Tree::Identifier::reducibile(void)
{
  return true;
}

TreePointer Tree::Identifier::reduce(void)
{
  throw "TODO";
}

}
