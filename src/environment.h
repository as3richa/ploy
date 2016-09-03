#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <cassert>
#include <string>

#include "gc.h"
#include "tree.h"

namespace ploy
{

class Environment: public GC
{
private:
  std::string key;
  const Tree* value;
  Environment* rest;

public:
  Environment(void) : key(""), value(nullptr) { ; };
  Environment(std::string key_, const Tree* value_, Environment* rest_) : key(key_), value(value_), rest(rest_)
  {
    assert(value && !value->reducibile());
  };

  void mutate(std::string key, const Tree *value);
  const Tree* find(std::string key);
};

}

#endif
