#ifndef _AND_H_
#define _AND_H_

#include <vector>
#include <string>

#include "tree.h"

namespace ploy
{

class Tree::And: public Tree
{
private:
  std::vector<const Tree*> params;

public:
  And(std::vector<const Tree*> params_) : params(params_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
