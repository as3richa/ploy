#ifndef _LET_H_
#define _LET_H_

#include "../tree.h"

#include <vector>
#include <algorithm>

namespace ploy
{

class Tree::Let: public Tree
{
private:
  std::vector<std::pair<std::string, const Tree*>> bindings;
  const Tree* body;

public:
  Let(std::vector<std::pair<std::string, const Tree*>> bindings_, const Tree* body_) :
    bindings(bindings_), body(body_) { ; }

  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
