#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <vector>
#include <string>

#include "../tree.h"

namespace ploy
{

class Tree::Application: public Tree
{
private:
  const Tree* fn;
  std::vector<const Tree*> params;

public:
  Application(const Tree* fn_, std::vector<const Tree*> params_) : fn(fn_), params(params_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
