#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <cstring>
#include <exception>
#include <string>

#include "tokenizer.h"

namespace ploy
{

class Error: public std::runtime_error
{
protected:
  char buffer[1024];

public:
  Error(void) : std::runtime_error("borked") { }
  virtual const char* what(void) const throw()
  {
    return buffer;
  };
};

class TokenError: public Error
{
public:
  Token token;

  TokenError(Token token_) : token(token_)
  {
    snprintf(this->buffer, sizeof(this->buffer), "%d:%d: invalid token (%s, lexeme '%s')",
      token.line, token.column, token.description().c_str(), token.lexeme.c_str());
  };

  TokenError(Token token_, std::string expected) : token(token_)
  {
    snprintf(this->buffer, sizeof(this->buffer), "%d:%d: unexpected %s '%s'; expected %s",
      token.line, token.column, token.description().c_str(), token.lexeme.c_str(), expected.c_str());
  }
};

class ParseError: public Error
{
public:
  ParseError(Token token, std::string expected)
  {
    snprintf(this->buffer, sizeof(this->buffer), "%d:%d: unexpected %s '%s'; expected %s",
      token.line, token.column, token.description().c_str(), token.lexeme.c_str(), expected.c_str());
  }

  ParseError(int line, int column, std::string expected)
  {
    snprintf(this->buffer, sizeof(this->buffer), "%d:%d: unexpected end of file; expected %s",
      line, column, expected.c_str());
  }
};

class RuntimeError: public Error
{
public:
  RuntimeError(std::string what)
  {
    strncpy(this->buffer, what.c_str(), sizeof(buffer) - 1);
    this->buffer[sizeof(this->buffer) - 1] = '\0';
  }
};

class RangeError: public Error
{
public:
  RangeError(std::string what)
  {
    strncpy(this->buffer, what.c_str(), sizeof(buffer) - 1);
    this->buffer[sizeof(this->buffer) - 1] = '\0';
  }
};

}

#endif
