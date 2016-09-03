#ifndef _GARBAGE_COLLECTED_H_
#define _GARBAGE_COLLECTED_H_

#include <algorithm>
#include <unordered_set>

namespace ploy
{

class GC
{
private:
  static std::unordered_set<const GC*> all;

public:
  template<typename _Tp, typename... _Args>
    static _Tp* gnew(_Args&&... __args)
    {
      _Tp* object = new _Tp(std::forward<_Args>(__args)...);
      all.insert(dynamic_cast<const GC*>(object));
      return object;
    }
};

}

#endif
