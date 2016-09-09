#ifndef _AST_BOOLEAN_H_
#define _AST_BOOLEAN_H_

#include <string>
#include "value.h"

namespace ploy { namespace AST
{

class Boolean: public Value
{
private:
  static const Boolean singletonFalse;
  static const Boolean singletonTrue;

public:
  const bool value;

  Boolean(bool value_) : value(value_) { ; }

  static const Boolean* fromBool(bool value);
  static const Boolean* fromLexeme(std::string lexeme);

  virtual std::string inspect(void) const;
};

}}

#endif
