#include <string>
#include "environment.h"
#include "ast/value.h"

namespace ploy
{

void Environment::mutate(std::string key, const AST::Value* value)
{
  assert("Environment value cannot be null" && value);

  this->rest = GC::gnew<Environment>(this->key, this->value, this->rest);
  this->key = key;
  this->value = value;
}

const AST::Value* Environment::find(std::string key)
{
  for(auto env = this; env->value != nullptr; env = env->rest)
  {
    if(env->key == key)
    {
      return env->value;
    }
  }

  return nullptr;
}

}
