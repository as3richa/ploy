#ifndef _GARBAGE_COLLECTED_H_
#define _GARBAGE_COLLECTED_H_

#include <algorithm>
#include <unordered_set>

namespace ploy
{

class GarbageCollected
{
private:
  static std::unordered_set<const GarbageCollected*> all;

public:
  GarbageCollected(void);

//  virtual std::vector<GarbageCollected *> links(void);

//  static void collect(GarbageCollected *root);
};

}

#endif
