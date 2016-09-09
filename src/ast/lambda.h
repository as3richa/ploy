#ifndef _AST_LAMBDA_H_
#define _AST_LAMBDA_H_

#include <vector>
#include "node.h"

namespace ploy { namespace AST
{

class Lambda: public Node
{
private:
  std::vector<std::string> identifiers;
  const Node* body;

public:
  Lambda(std::vector<std::string> identifiers_, const Node* body_) : identifiers(identifiers_), body(body_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
