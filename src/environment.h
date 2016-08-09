#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <string>

#include "garbage_collected.h"
#include "tree.h"

namespace ploy
{

class Environment: public GarbageCollected
{
private:
  std::string key;
  Tree* value;
  Environment* rest;

public:
  Environment(void) : key(""), value(nullptr) { ; };
  Environment(std::string key_, Tree* value_, Environment* rest_) : key(key_), value(value_), rest(rest_) { ; };
  void mutate(std::string key, Tree *value);
};

}

#endif
