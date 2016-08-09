#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_

#include <istream>
#include <memory>

#include "tree.h"

namespace ploy
{

TreePointer execute(std::istream& stream);

}

#endif
