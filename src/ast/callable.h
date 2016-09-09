#ifndef _AST_CALLABLE_H_
#define _AST_CALLABLE_H_

#include <vector>
#include "node.h"

namespace ploy { namespace AST
{

class Callable: public Value
{
public:
  virtual const Value* apply(std::vector<const Value*>) const = 0;
};

}}

#endif
