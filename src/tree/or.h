#ifndef _OR_H_
#define _OR_H_

#include <vector>
#include <string>

#include "../tree.h"

namespace ploy
{

class Tree::Or: public Tree
{
private:
  std::vector<const Tree*> params;

public:
  Or(std::vector<const Tree*> params_) : params(params_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
