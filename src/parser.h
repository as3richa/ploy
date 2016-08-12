#ifndef _PARSER_H_
#define _PARSER_H_

#include <istream>
#include <memory>

#include "tree.h"

namespace ploy
{

std::vector<const Tree*> parse(std::istream& input);

}

#endif
