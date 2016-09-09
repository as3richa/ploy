#ifndef _AST_AND_H_
#define _AST_AND_H_

#include <vector>
#include "node.h"

namespace ploy { namespace AST
{

class And: public Node
{
private:
  std::vector<const Node*> params;

public:
  And(std::vector<const Node*> params_) : params(params_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
