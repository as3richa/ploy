#include "definition.h"

namespace ploy { namespace AST
{

const Value* Definition::reduce(Environment* env) const
{
  env->mutate(this->identifier, this->body->reduce(env));
  return nullptr;
}

}}
