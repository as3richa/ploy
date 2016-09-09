#include <iostream>
#include <istream>
#include <memory>
#include "executor.h"
#include "parser.h"
#include "standard_library.h"

namespace ploy
{

void execute(std::istream& stream)
{
  auto env = standardLibrary();
  for(auto expression : parse(stream))
  {
    std::cout << expression->reduce(env);
  }
}

}
