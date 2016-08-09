#ifndef _OR_H_
#define _OR_H_

#include <list>
#include <string>

#include "../tree.h"

namespace ploy
{

class Tree::Or: public Tree
{
private:
  std::list<TreePointer> params;

public:
  Or(std::list<TreePointer> params_) : params(params_) { ; }
  virtual std::string inspect(void);
  virtual bool reducibile(void);
  virtual TreePointer reduce(void);
  virtual std::string description(void);
};

}

#endif
