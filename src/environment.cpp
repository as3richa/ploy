#include "environment.h"

#include <memory>
#include <string>

#include "tree.h"

namespace ploy
{

void Environment::mutate(std::string key, Tree *value)
{
  this->rest = new Environment(this->key, this->value, this->rest);
  this->key = key;
  this->value = value;
}

}
