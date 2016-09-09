#ifndef _AST_NODE_H_
#define _AST_NODE_H_

#include "../gc.h"

namespace ploy
{

class Environment;

}

namespace ploy { namespace AST
{

class Value;

class Node: public GC
{
public:
  virtual const Value* reduce(Environment*) const = 0;
  virtual ~Node(void) { ; }
};

}}

#include "value.h"
#include "../environment.h"

#endif
