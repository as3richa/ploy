#ifndef _COND_H_
#define _COND_H_

#include "../tree.h"

namespace ploy
{

class Tree::Cond: public Tree
{
private:
  std::vector<std::pair<const Tree*, const Tree*>> branches;
  const Tree* else_branch;

public:
  Cond(std::vector<std::pair<const Tree*, const Tree*>> branches_, const Tree* else_branch_) :
    branches(branches_), else_branch(else_branch_) { ; }

  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
