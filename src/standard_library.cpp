#include <sstream>
#include "library.h"
#include "parser.h"
#include "standard_library.h"
#include "ast/ast.h"

namespace ploy
{

const AST::Value* notCallback(std::vector<const AST::Value*>);
const AST::Value* addCallback(std::vector<const AST::Value*>);
const AST::Value* subCallback(std::vector<const AST::Value*>);
const AST::Value* mulCallback(std::vector<const AST::Value*>);
const AST::Value* divCallback(std::vector<const AST::Value*>);
const AST::Value* zeroCallback(std::vector<const AST::Value*>);
const AST::Value* eqCallback(std::vector<const AST::Value*>);
const AST::Value* consCallback(std::vector<const AST::Value*>);
const AST::Value* firstCallback(std::vector<const AST::Value*>);
const AST::Value* restCallback(std::vector<const AST::Value*>);
const AST::Value* listCallback(std::vector<const AST::Value*>);

struct
{
  std::string name;
  const AST::Value* (*callback)(std::vector<const AST::Value*>);
  int min_arity;
  int max_arity;
} builtin_functions[] = {
  {"not", notCallback, 1, 1},
  {"+", addCallback, 0, AST::BuiltinFunction::InfiniteArity},
  {"-", subCallback, 1, AST::BuiltinFunction::InfiniteArity},
  {"*", mulCallback, 0, AST::BuiltinFunction::InfiniteArity},
  {"/", divCallback, 1, AST::BuiltinFunction::InfiniteArity},
  {"zero?", zeroCallback, 1, 1},
  {"eq?", eqCallback, 2, AST::BuiltinFunction::InfiniteArity},
  {"cons", consCallback, 2, 2},
  {"first", firstCallback, 1, 1},
  {"rest", restCallback, 1, 1},
  {"list", listCallback, 0, AST::BuiltinFunction::InfiniteArity}
};

Environment* libraryEnvironment = nullptr;
const AST::Value* empty;
const AST::Value* sTrue;
const AST::Value* sFalse;

Environment* standardLibrary(void)
{
  if(libraryEnvironment == nullptr)
  {
    static std::istringstream library_stream(library);
    auto scheme_library = parse(library_stream);

    libraryEnvironment = new Environment();
    for(auto bf : builtin_functions)
    {
      libraryEnvironment = new Environment(
        bf.name,
        new AST::BuiltinFunction(
          bf.name,
          bf.callback,
          bf.min_arity,
          bf.max_arity
        ),
        libraryEnvironment
      );
    }

    empty = new AST::Singleton("empty");
    libraryEnvironment = new Environment("empty", empty, libraryEnvironment);

    for(auto expression : scheme_library)
    {
      expression->reduce(libraryEnvironment);
    }
  }

  return libraryEnvironment;
}

const AST::Value* notCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() == 1);

  auto casted = dynamic_cast<const AST::Boolean*>(params[0]);
  return AST::Boolean::fromBool(casted && casted->value == false);
}

const AST::Value* mulCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() >= 0);

  mpq_class result(1);
  for(auto param : params)
  {
    auto factor = dynamic_cast<const AST::Number*>(param);
    if(!factor)
    {
      throw "TODO";
    }
    else
    {
      result *= factor->value;
    }
  }

  return new AST::Number(result);
}

const AST::Value* addCallback(std::vector<const AST::Value*> params)
{
  mpq_class result(0);
  for(auto param : params)
  {
    auto summand = dynamic_cast<const AST::Number*>(param);
    if(!summand)
    {
      throw "TODO";
    }
    else
    {
      result += summand->value;
    }
  }

  return new AST::Number(result);
}

const AST::Value* subCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() >= 1);
  if(params.size() == 1)
  {
    auto first = dynamic_cast<const AST::Number*>(params[0]);
    if(!first)
    {
      throw "TODO";
    }
    else
    {
      return new AST::Number(-first->value);
    }
  }
  else
  {
    auto first = dynamic_cast<const AST::Number*>(params[0]);
    if(!first)
    {
      throw "TODO";
    }
    else
    {
      mpq_class result = first->value;
      for(int i = 1; i < (int)params.size(); i ++)
      {
        auto number = dynamic_cast<const AST::Number*>(params[i]);
        if(!number)
        {
          throw "TODO";
        }
        result -= number->value;
      }

      return new AST::Number(result);
    }
  }
}

const AST::Value* divCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() >= 1);
  if(params.size() == 1)
  {
    auto first = dynamic_cast<const AST::Number*>(params[0]);
    if(!first)
    {
      throw "TODO";
    }
    else
    {
      return new AST::Number(1/first->value);
    }
  }
  else
  {
    auto first = dynamic_cast<const AST::Number*>(params[0]);
    if(!first)
    {
      throw "TODO";
    }
    else
    {
      mpq_class result = first->value;
      for(int i = 1; i < (int)params.size(); i ++)
      {
        auto number = dynamic_cast<const AST::Number*>(params[i]);
        if(!number)
        {
          throw "TODO";
        }
        result /= number->value;
      }

      return new AST::Number(result);
    }
  }
}

const AST::Value* zeroCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() == 1);
  auto number = dynamic_cast<const AST::Number*>(params[0]);
  return AST::Boolean::fromBool(number && number->value == 0);
}

const AST::Value* eqCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() == 2);
  return AST::Boolean::fromBool(params[0]->eq(params[1]));
}

const AST::Value* consCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() == 2);
  return new AST::Cons(params[0], params[1]);
}

const AST::Value* firstCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() == 1);
  auto casted = dynamic_cast<const AST::Cons*>(params[0]);
  if(!casted)
  {
    throw "TODO";
  }
  return casted->first;
}

const AST::Value* restCallback(std::vector<const AST::Value*> params)
{
  assert(params.size() == 1);
  auto casted = dynamic_cast<const AST::Cons*>(params[0]);
  if(!casted)
  {
    throw "TODO";
  }
  return casted->rest;
}

const AST::Value* listCallback(std::vector<const AST::Value*> params)
{
  const AST::Value* result = empty;
  for(int i = (int)params.size(); i --;)
  {
    result = new AST::Cons(params[i], result);
  }
  return result;
}

}
