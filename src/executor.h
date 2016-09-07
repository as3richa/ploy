#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_

#include <istream>
#include <memory>

#include "ast/tree.h"

namespace ploy
{

void execute(std::istream& stream);

}

#endif
