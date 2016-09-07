#include "singleton.h"

#include <string>

namespace ploy
{

std::string Tree::Singleton::inspect(void) const
{
  return this->identifier;
}

}
