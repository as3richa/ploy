#ifndef _AST_COND_H_
#define _AST_COND_H_

#include <vector>
#include "node.h"

namespace ploy { namespace AST
{

class Cond: public Node
{
private:
  std::vector<std::pair<const Node*, const Node*>> branches;
  const Node* else_branch;

public:
  Cond(std::vector<std::pair<const Node*, const Node*>> branches_, const Node* else_branch_) :
    branches(branches_), else_branch(else_branch_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
