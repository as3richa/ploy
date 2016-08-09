#include "tree.h"

#include <memory>
#include <string>
#include <cassert>

namespace ploy
{

bool Tree::Value::reducibile(void)
{
  return false;
}

TreePointer Tree::Value::reduce(void)
{
  assert(false && "value type is not reducibile");
  return nullptr;
}

}
