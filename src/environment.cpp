#include "environment.h"

#include <memory>
#include <string>

#include "tree.h"

namespace ploy
{

void Environment::mutate(std::string key, const Tree *value)
{
  assert(!value->reducibile());

  this->rest = new Environment(this->key, this->value, this->rest);
  this->key = key;
  this->value = value;
}

const Tree* Environment::find(std::string key)
{
  for(auto env = this; env->value; env = env->rest)
  {
    if(env->key == key)
    {
      return env->value;
    }
  }

  return nullptr;
}

}
