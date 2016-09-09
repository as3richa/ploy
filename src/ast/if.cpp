#include "if.h"
#include "boolean.h"

namespace ploy { namespace AST
{

const Value* If::reduce(Environment* env) const
{
  auto conditional = dynamic_cast<const Boolean*>(this->conditional->reduce(env));
  if(conditional && conditional->value == false)
  {
    return this->false_branch->reduce(env);
  }
  else
  {
    return this->true_branch->reduce(env);
  }
}

}}
