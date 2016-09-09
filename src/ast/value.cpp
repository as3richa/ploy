#include "value.h"

namespace ploy { namespace AST {

bool Value::eq(const Value* other) const
{
  return (this == other);
}

const Value* Value::reduce(Environment* env) const
{
  (void)env;
  return this;
}

std::ostream& operator<<(std::ostream& os, const Value* v)
{
  if(v)
  {
    os << v->inspect() << '\n';
  }

  return os;
}

}}
