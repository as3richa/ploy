#ifndef _AST_IF_H_
#define _AST_IF_H_

#include "node.h"

namespace ploy { namespace AST
{

class If: public Node
{
private:
  const Node* conditional;
  const Node* true_branch;
  const Node* false_branch;

public:
  If(const Node* conditional_, const Node* true_branch_, const Node* false_branch_) :
    conditional(conditional_), true_branch(true_branch_), false_branch(false_branch_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
