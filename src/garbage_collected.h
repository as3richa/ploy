#ifndef _GARBAGE_COLLECTED_H_
#define _GARBAGE_COLLECTED_H_

#include <set>

namespace ploy
{

class GarbageCollected
{
private:
  std::set<GarbageCollected*> all;

public:
  GarbageCollected(void);

//  virtual std::vector<GarbageCollected *> links(void);

//  static void collect(GarbageCollected *root);
};

}

#endif
