#ifndef _IDENTIFIER_H_
#define _IDENTIFIER_H_

#include "../tree.h"

namespace ploy
{

class Tree::Identifier: public Tree
{
private:
  std::string lexeme;

public:
  Identifier(std::string lexeme_) : lexeme(lexeme_) { ; }
  virtual std::string inspect(void) const;
  virtual const Tree* reduce(Environment*) const;
};

}

#endif
