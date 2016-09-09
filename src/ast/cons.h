#ifndef _AST_CONS_H_
#define _AST_CONS_H_

#include "value.h"

namespace ploy { namespace AST
{

class Cons: public Value
{
public:
  const Value* const first;
  const Value* const rest;

  Cons(const Value* first_, const Value* rest_) : first(first_), rest(rest_) { ; }
  virtual std::string inspect(void) const;
};

}}

#endif
