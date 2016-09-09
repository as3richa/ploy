#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <cassert>
#include <string>
#include "gc.h"
#include "ast/value.h"

namespace ploy
{

class Environment: public GC
{
private:
  std::string key;
  const AST::Value* value;
  Environment* rest;

public:
  Environment(void) : key(""), value(nullptr) { ; };
  Environment(std::string key_, const AST::Value* value_, Environment* rest_) : key(key_), value(value_), rest(rest_)
  {
    assert("Environment value cannot be null" && value);
  };

  void mutate(std::string key, const AST::Value* value);
  const AST::Value* find(std::string key);
};

}

#endif
