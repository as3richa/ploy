#ifndef _AST_VALUE_H_
#define _AST_VALUE_H_

#include <iostream>
#include <string>
#include "node.h"

namespace ploy { namespace AST
{

class Value: public Node
{
public:
  virtual bool eq(const Value*) const;
  virtual std::string inspect(void) const = 0;
  virtual const Value* reduce(Environment*) const;
};

std::ostream& operator<<(std::ostream&, const Value*);

}}

#endif
