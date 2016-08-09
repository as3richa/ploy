#ifndef _TREE_H_
#define _TREE_H_

#include <string>

#include "garbage_collected.h"

namespace ploy
{

class Tree;
typedef Tree* TreePointer;

class Tree: public GarbageCollected
{
public:
  class Value;

  class And;
  class Application;
  class Boolean;
  class Cons;
  class Identifier;
  class Lambda;
  class Let;
  class Number;
  class Or;

  Tree(void) { ; }
  virtual std::string inspect(void) = 0;
  virtual bool reducibile(void) = 0;
  virtual TreePointer reduce(void) = 0;
  virtual ~Tree(void) { ; }
};

class Tree::Value: public Tree
{
public:
  virtual bool reducibile(void);
  virtual TreePointer reduce(void);
};

}

#include "tree/and.h"
#include "tree/application.h"
#include "tree/boolean.h"
#include "tree/cons.h"
#include "tree/identifier.h"
#include "tree/lambda.h"
#include "tree/let.h"
#include "tree/number.h"
#include "tree/or.h"

#endif
