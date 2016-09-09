#ifndef _LET_H_
#define _LET_H_

#include <vector>
#include <algorithm>
#include "node.h"

namespace ploy { namespace AST
{

class Let: public Node
{
private:
  std::vector<std::pair<std::string, const Node*>> bindings;
  const Node* body;

public:
  Let(std::vector<std::pair<std::string, const Node*>> bindings_, const Node* body_) :
    bindings(bindings_), body(body_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
