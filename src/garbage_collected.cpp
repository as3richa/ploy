#include "garbage_collected.h"

#include <iostream>

namespace ploy
{

std::unordered_set<const GarbageCollected*> GarbageCollected::all;

GarbageCollected::GarbageCollected(void)
{
  GarbageCollected::all.insert(this);
  //std::cout << GarbageCollected::all.size() << '\n';
}

}
