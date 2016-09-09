#include "let.h"
#include "../gc.h"

namespace ploy { namespace AST
{

const Value* Let::reduce(Environment* env) const
{
  auto new_env = env;
  for(auto& binding : this->bindings)
  {
    new_env = GC::gnew<Environment>(binding.first, binding.second->reduce(env), new_env);
  }
  return this->body->reduce(new_env);
}

}}
