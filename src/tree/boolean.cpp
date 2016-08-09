#include "boolean.h"
#include "../exceptions.h"

namespace ploy
{

std::string Tree::Boolean::inspect(void)
{
  return (this->value) ? "#t" : "#f";
}

}
