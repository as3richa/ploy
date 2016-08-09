#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <list>
#include <string>

#include "../tree.h"

namespace ploy
{

class Tree::Application: public Tree
{
private:
  TreePointer fn;
  std::list<TreePointer> params;

public:
  Application(TreePointer fn_, std::list<TreePointer> params_) : fn(fn_), params(params_) { ; }
  virtual std::string inspect(void);
  virtual bool reducibile(void);
  virtual TreePointer reduce(void);
};

}

#endif
