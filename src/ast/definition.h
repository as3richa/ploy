#ifndef _AST_DEFINITION_H_
#define _AST_DEFINITION_H_

#include "node.h"

namespace ploy { namespace AST
{

class Definition: public Node
{
private:
  std::string identifier;
  const Node* body;

public:
  Definition(std::string identifier_, const Node* body_) : identifier(identifier_), body(body_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
