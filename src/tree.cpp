#include "tree.h"

#include <memory>
#include <iostream>
#include <string>
#include <cassert>

namespace ploy
{

bool Tree::reducibile(void) const
{
  return true;
}

bool Tree::eq(const Tree* other) const
{
  return (this == other);
}

bool Tree::Value::reducibile(void) const
{
  return false;
}

const Tree* Tree::Value::reduce(Environment* env) const
{
  (void)env;
  return this;
}

std::ostream& operator<<(std::ostream& os, const Tree* tree)
{
  if(tree)
  {
    os << tree->inspect() << '\n';
  }

  return os;
}

}
