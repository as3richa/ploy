#ifndef _AST_OR_H_
#define _AST_OR_H_

#include <vector>
#include "node.h"

namespace ploy { namespace AST
{

class Or: public Node
{
private:
  std::vector<const Node*> params;

public:
  Or(std::vector<const Node*> params_) : params(params_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
