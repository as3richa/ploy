#ifndef _LET_H_
#define _LET_H_

#include "../tree.h"

#include <list>
#include <algorithm>

namespace ploy
{

class Tree::Let: public Tree
{
private:
  std::list<std::pair<std::string, TreePointer>> bindings;
  TreePointer body;

public:
  Let(std::list<std::pair<std::string, TreePointer>> bindings_, TreePointer body_) :
    bindings(bindings_), body(body_) { ; }

  virtual std::string inspect(void);
  virtual bool reducibile(void);
  virtual TreePointer reduce(void);
};

}

#endif
