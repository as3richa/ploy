#include "boolean.h"
#include "../exceptions.h"

namespace ploy
{

std::string Tree::Boolean::inspect(void) const
{
  return (this->value) ? "#t" : "#f";
}

}
