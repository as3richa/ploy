#include "lambda.h"
#include "closure.h"
#include "../gc.h"

namespace ploy { namespace AST
{

const Value* Lambda::reduce(Environment* env) const
{
  return GC::gnew<Closure>(this->identifiers, this->body, env);
}

}}
