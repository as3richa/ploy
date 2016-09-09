#include <cassert>
#include "boolean.h"

namespace ploy { namespace AST
{

const Boolean Boolean::singletonFalse(false);
const Boolean Boolean::singletonTrue(true);

std::string Boolean::inspect(void) const
{
  return (this->value) ? "#t" : "#f";
}

const Boolean* Boolean::fromBool(bool value)
{
  return (value) ? &Boolean::singletonTrue : &Boolean::singletonFalse;
}

const Boolean* Boolean::fromLexeme(std::string lexeme)
{
  assert("Boolean literal must be either \"#t\" or \"#f\"" && (lexeme == "#t" || lexeme == "#f"));
  return Boolean::fromBool(lexeme == "#t");
}

}}
