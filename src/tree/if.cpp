#include "if.h"

#include "../tree.h"

namespace ploy
{

std::string Tree::If::inspect(void) const
{
  return std::string("(if ") +
    this->conditional->inspect() + " " +
    this->true_branch->inspect() + " " +
    this->false_branch->inspect() + ")";
}

const Tree* Tree::If::reduce(Environment* env) const
{
  auto conditional = dynamic_cast<const Tree::Boolean*>(this->conditional->reduce(env));
  if(conditional && conditional->value == false)
  {
    return this->false_branch->reduce(env);
  }
  else
  {
    return this->true_branch->reduce(env);
  }
}

}
