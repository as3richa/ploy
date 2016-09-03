#include "boolean.h"
#include "../exceptions.h"

namespace ploy
{

const Tree::Boolean Tree::Boolean::singletonFalse(false);
const Tree::Boolean Tree::Boolean::singletonTrue(true);

std::string Tree::Boolean::inspect(void) const
{
  return (this->value) ? "#t" : "#f";
}

const Tree::Boolean* Tree::Boolean::fromValue(bool value)
{
  return (value) ? &Tree::Boolean::singletonTrue : &Tree::Boolean::singletonFalse;
}

const Tree::Boolean* Tree::Boolean::fromLexeme(std::string lexeme)
{
  assert(lexeme == "#t" || lexeme == "#f");
  return Tree::Boolean::fromValue(lexeme == "#t");
}

}
