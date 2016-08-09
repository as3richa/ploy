#ifndef _PARSER_H_
#define _PARSER_H_

#include <istream>
#include <memory>

#include "tree.h"

namespace ploy
{

TreePointer parse(std::istream& input);

}

#endif
