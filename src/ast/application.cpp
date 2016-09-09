#include <cassert>
#include "application.h"
#include "callable.h"

namespace ploy { namespace AST {

const Value* Application::reduce(Environment* env) const
{
  auto fn = dynamic_cast<const Callable*>(this->fn->reduce(env));
  if(!fn)
  {
    throw "TODO (not Callable)";
  }
  else
  {
    std::vector<const Value*> reduced_params;
    for(auto& param : this->params)
    {
      reduced_params.push_back(param->reduce(env));
    }
    return fn->apply(reduced_params);
  }
}

}}
