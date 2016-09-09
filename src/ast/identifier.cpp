#include "identifier.h"
#include "../exceptions.h"

namespace ploy { namespace AST
{

const Value* Identifier::reduce(Environment* env) const
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

}}
