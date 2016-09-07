#include "identifier.h"

#include <string>

#include "../environment.h"
#include "tree.h"
#include "../exceptions.h"

namespace ploy
{

std::string Tree::Identifier::inspect(void) const
{
  return this->lexeme;
}

const Tree* Tree::Identifier::reduce(Environment* env) const
{
  auto value = env->find(this->lexeme);
  if(!value)
  {
    throw UndefinedIdentifierError(this->lexeme);
  }
  else
  {
    return value;
  }
}

}
