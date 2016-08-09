#include "executor.h"

#include <iostream>
#include <istream>
#include <memory>

#include "parser.h"
#include "tree.h"

namespace ploy
{

TreePointer execute(std::istream& stream)
{
  return parse(stream);
}

}
