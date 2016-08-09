#ifndef _AND_H_
#define _AND_H_

#include <list>
#include <string>

#include "../tree.h"

namespace ploy
{

class Tree::And: public Tree
{
private:
  std::list<TreePointer> params;

public:
  And(std::list<TreePointer> params_) : params(params_) { ; }
  virtual std::string inspect(void);
  virtual bool reducibile(void);
  virtual TreePointer reduce(void);
};

}

#endif
