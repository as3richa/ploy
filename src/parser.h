#ifndef _PARSER_H_
#define _PARSER_H_

#include <istream>
#include <memory>
#include "ast/ast.h"

namespace ploy
{

std::vector<const AST::Node*> parse(std::istream& input);

}

#endif
