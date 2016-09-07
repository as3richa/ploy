#ifndef _IF_H_
#define _IF_H_

#include "tree.h"

namespace ploy
{

class Tree::If: public Tree
{
private:
  const Tree* conditional;
  const Tree* true_branch;
  const Tree* false_branch;

public:
  If(const Tree* conditional_, const Tree* true_branch_, const Tree* false_branch_) :
    conditional(conditional_), true_branch(true_branch_), false_branch(false_branch_) { ; }

  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
