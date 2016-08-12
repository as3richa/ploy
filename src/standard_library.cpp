#include "standard_library.h"

#include <sstream>

#include "tree.h"
#include "tree/builtin_function.h"
#include "tree/singleton.h"

#include "parser.h"
#include "library.h"

namespace ploy
{

typedef const Tree* Callback(std::vector<const Tree*>);

const Tree* notCallback(std::vector<const Tree*>);
const Tree* addCallback(std::vector<const Tree*>);
const Tree* subCallback(std::vector<const Tree*>);
const Tree* mulCallback(std::vector<const Tree*>);
const Tree* zeroCallback(std::vector<const Tree*>);
const Tree* eqCallback(std::vector<const Tree*>);
const Tree* consCallback(std::vector<const Tree*>);
const Tree* firstCallback(std::vector<const Tree*>);
const Tree* restCallback(std::vector<const Tree*>);
const Tree* emptyCallback(std::vector<const Tree*>);
const Tree* listCallback(std::vector<const Tree*>);

const Tree* empty = new Tree::Singleton("empty");

struct
{
  std::string name;
  const Tree* (*callback)(std::vector<const Tree *>);
  int min_arity;
  int max_arity;
} builtin_functions[] = {
  {"not", notCallback, 1, 1},
  {"+", addCallback, 0, Tree::BuiltinFunction::InfiniteArity},
  {"-", subCallback, 1, Tree::BuiltinFunction::InfiniteArity},
  {"*", mulCallback, 0, Tree::BuiltinFunction::InfiniteArity},
  {"zero?", zeroCallback, 1, 1},
  {"eq?", eqCallback, 2, Tree::BuiltinFunction::InfiniteArity},
  {"cons", consCallback, 2, 2},
  {"first", firstCallback, 1, 1},
  {"rest", restCallback, 1, 1},
  {"empty?", emptyCallback, 1, 1},
  {"list", listCallback, 0, Tree::BuiltinFunction::InfiniteArity}
};
const int n_builtin_functions = sizeof(builtin_functions) / sizeof(builtin_functions[0]);

Environment* standardLibraryEnvironment(void)
{
  static std::istringstream library_stream(library);
  static std::vector<const Tree*> scheme_library = parse(library_stream);

  auto env = new Environment();
  for(int i = 0; i < n_builtin_functions; i ++)
  {
    env = new Environment(
      builtin_functions[i].name,
      new Tree::BuiltinFunction(
        builtin_functions[i].name,
        builtin_functions[i].callback,
        builtin_functions[i].min_arity,
        builtin_functions[i].max_arity
      ),
      env
    );
  }
  env = new Environment("empty", empty, env);

  for(auto expression : scheme_library)
  {
    expression->reduce(env);
  }

  return env;
}

const Tree* notCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 1);

  auto casted = dynamic_cast<const Tree::Boolean*>(params[0]);
  return new Tree::Boolean(casted && casted->value == false);
}

const Tree* mulCallback(std::vector<const Tree*> params)
{
  assert(params.size() >= 0);

  mpq_class result(1);
  for(auto param : params)
  {
    auto factor = dynamic_cast<const Tree::Number*>(param);
    if(!factor)
    {
      throw "TODO";
    }
    else
    {
      result *= factor->value;
    }
  }

  return new Tree::Number(result);
}

const Tree* addCallback(std::vector<const Tree*> params)
{
  mpq_class result(0);
  for(auto param : params)
  {
    auto summand = dynamic_cast<const Tree::Number*>(param);
    if(!summand)
    {
      throw "TODO";
    }
    else
    {
      result += summand->value;
    }
  }

  return new Tree::Number(result);
}

const Tree* subCallback(std::vector<const Tree*> params)
{
  assert(params.size() >= 1);
  if(params.size() < 2)
  {
    throw "TODO";
  }
  else
  {
    auto first = dynamic_cast<const Tree::Number*>(params[0]);
    if(!first)
    {
      throw "TODO";
    }
    else
    {
      mpq_class result = first->value;
      for(int i = 1; i < (int)params.size(); i ++)
      {
        auto number = dynamic_cast<const Tree::Number*>(params[i]);
        if(!number)
        {
          throw "TODO";
        }
        result -= number->value;
      }

      return new Tree::Number(result);
    }
  }
}

const Tree* zeroCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 1);
  auto number = dynamic_cast<const Tree::Number*>(params[0]);
  return new Tree::Boolean(number && number->value == 0);
}

const Tree* eqCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 2);
  return new Tree::Boolean(params[0]->eq(params[1]));
}

const Tree* consCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 2);
  return new Tree::Cons(params[0], params[1]);
}

const Tree* firstCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 1);
  auto casted = dynamic_cast<const Tree::Cons*>(params[0]);
  if(!casted)
  {
    throw "TODO";
  }
  return casted->first;
}

const Tree* restCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 1);
  auto casted = dynamic_cast<const Tree::Cons*>(params[0]);
  if(!casted)
  {
    throw "TODO";
  }
  return casted->rest;
}

const Tree* emptyCallback(std::vector<const Tree*> params)
{
  assert(params.size() == 1);
  return new Tree::Boolean(params[0] == empty);
}

const Tree* listCallback(std::vector<const Tree*> params)
{
  const Tree* result = empty;
  for(int i = (int)params.size(); i --;)
  {
    result = new Tree::Cons(params[i], result);
  }
  return result;
}

}