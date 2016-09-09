#ifndef _AST_APPLICATION_H_
#define _AST_APPLICATION_H_

#include <vector>
#include "node.h"

namespace ploy { namespace AST
{

class Application: public Node
{
private:
  const Node* fn;
  std::vector<const Node*> params;

public:
  Application(const Node* fn_, std::vector<const Node*> params_) : fn(fn_), params(params_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
