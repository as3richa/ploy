#include "executor.h"

#include <iostream>
#include <istream>
#include <memory>

#include "environment.h"
#include "parser.h"
#include "tree.h"
#include "standard_library.h"

namespace ploy
{

void execute(std::istream& stream)
{
  auto env = standardLibraryEnvironment();
  for(auto expression : parse(stream))
  {
    std::cout << expression->reduce(env);
  }
}

}
