#ifndef _AST_IDENTIFIER_H_
#define _AST_IDENTIFIER_H_

#include "node.h"

namespace ploy { namespace AST
{

class Identifier: public Node
{
private:
  std::string lexeme;

public:
  Identifier(std::string lexeme_) : lexeme(lexeme_) { ; }
  virtual const Value* reduce(Environment*) const;
};

}}

#endif
