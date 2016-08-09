#include "garbage_collected.h"

#include <iostream>

namespace ploy
{
  GarbageCollected::GarbageCollected(void)
  {
    this->all.insert(this);
  }
}
