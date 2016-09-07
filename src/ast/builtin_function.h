#ifndef _BUILTIN_FUNCTION_H_
#define _BUILTIN_FUNCTION_H_

#include "tree.h"

namespace ploy
{

class Tree::BuiltinFunction: public Tree::Callable
{
private:
  typedef const Tree* (*Callback)(std::vector<const Tree*>);

  std::string identifier;
  Callback callback;
  int min_arity;
  int max_arity;

public:
  static const int InfiniteArity = (100 * 1000 * 1000);

  BuiltinFunction(std::string identifier_, Callback callback_, int min_arity_ = 0, int max_arity_ = InfiniteArity) :
    identifier(identifier_), callback(callback_), min_arity(min_arity_), max_arity(max_arity_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* apply(std::vector<const Tree*>) const;
};

}

#endif
