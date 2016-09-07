#ifndef _TREE_H_
#define _TREE_H_

#include <string>
#include <vector>

#include "../gc.h"

namespace ploy
{

class Environment;

class Tree: public GC
{
public:
  class Value;
  class Callable;

  class And;
  class Application;
  class Boolean;
  class BuiltinFunction;
  class Closure;
  class Cond;
  class Cons;
  class Definition;
  class Identifier;
  class If;
  class Lambda;
  class Let;
  class Number;
  class Or;
  class Singleton;

  Tree(void) { ; }
  virtual std::string inspect(void) const = 0;
  virtual bool reducibile(void) const;
  virtual const Tree* reduce(Environment*) const = 0;
  virtual bool eq(const Tree*) const;
  virtual ~Tree(void) { ; }
};

class Tree::Value: public Tree
{
public:
  virtual bool reducibile(void) const;
  virtual const Tree* reduce(Environment*) const;
};


class Tree::Callable: public Tree::Value
{
public:
  virtual const Tree* apply(std::vector<const Tree*>) const = 0;
};

std::ostream& operator<<(std::ostream&, const Tree*);

}

#include "and.h"
#include "application.h"
#include "boolean.h"
#include "closure.h"
#include "cond.h"
#include "cons.h"
#include "definition.h"
#include "identifier.h"
#include "if.h"
#include "lambda.h"
#include "let.h"
#include "number.h"
#include "or.h"
#include "singleton.h"

#endif
