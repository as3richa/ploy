#include "tokenizer.h"

#include <cassert>
#include <istream>
#include <vector>
#include <map>

#include "tracked_stream.h"
#include "exceptions.h"

namespace ploy
{

const std::map<Token::Type, std::string> descriptions = {
  {Token::NIL, "unknown token"},
  {Token::NUMBER_WITH_TRAILING_POINT, "incomplete numeric literal"},
  {Token::NUMBER_WITH_TRAILING_E, "incomplete numeric literal"},
  {Token::NUMBER_WITH_TRAILING_E_SIGN, "incomplete numeric literal"},
  {Token::HASH, "hash sign"},

  {Token::WHITESPACE, "whitespace"},
  {Token::COMMENT, "comment"},
  {Token::OPEN_PAREN, "open parenthesis or bracket"},
  {Token::CLOSE_PAREN, "close parenthesis or bracket"},
  {Token::IF, "if conditional"},
  {Token::LET, "let binding"},
  {Token::LAMBDA, "lambda function"},
  {Token::AND, "and conditional"},
  {Token::OR, "or conditional"},
  {Token::CONS, "cons pair"},
  {Token::NUMBER, "numeric literal"},
  {Token::IDENTIFIER, "identifier"},
  {Token::BOOLEAN, "boolean literal"}
};

const std::map<std::string, Token::Type> keywords = {
  {"if", Token::IF},
  {"and", Token::AND},
  {"or", Token::OR},
  {"let", Token::LET},
  {"lambda", Token::LAMBDA},
  {"cons", Token::CONS}
};

Token::Type transition(Token::Type prev, int c);
bool isid(int c);

Token Scanner::scan(void)
{
  if(this->unscanned)
  {
    this->unscanned = false;
    return this->previous;
  }

  Token token = this->scanAny();

  if(
    this->previous.type != Token::OPEN_PAREN &&
    this->previous.type != Token::CLOSE_PAREN &&
    token.type != Token::OPEN_PAREN &&
    token.type != Token::CLOSE_PAREN &&
    !this->spaced
  )
  {
    throw TokenError(token, "delimiting whitespace between non-parenthetical tokens");
  }

  this->spaced = false;
  while(!this->eof())
  {
    Token::Type next = transition(Token::NIL, this->stream.peek());
    if(next != Token::WHITESPACE && next != Token::COMMENT)
      break;

    this->spaced = true;
    this->scanAny();
  }

  return (this->previous = token);
}

void Scanner::unscan(void)
{
  assert(!this->unscanned && "can't unscan two tokens consecutively");
  this->unscanned = true;
}

Token Scanner::scanAny(void)
{
  Token token(this->stream.line, this->stream.column);

  while(!this->stream.eof())
  {
    int c = this->stream.peek();
    Token::Type next = transition(token.type, c);

    if(next == Token::NIL)
      break;

    token.type = next;
    token.lexeme += c;
    this->stream.get();
  }

  if(token.type == Token::IDENTIFIER)
  {
    std::map<std::string, Token::Type>::const_iterator it = keywords.find(token.lexeme);
    if(it != keywords.end())
      token.type = it->second;
  }
  else if(token.type == Token::ZERO || token.type == Token::NATURAL_NUMBER || token.type == Token::DECIMAL_NUMBER)
  {
    token.type = Token::NUMBER;
  }

  if(!token.acceptable())
    throw TokenError(token);

  return token;
}

Token::Type transition(Token::Type state, int c)
{
  if(c == EOF)
  {
    return Token::NIL;
  }
  else if(state == Token::NIL && c == '0')
  {
    // '' --> '0'
    return Token::ZERO;
  }
  else if((state == Token::NIL || state == Token::NATURAL_NUMBER) && isdigit(c))
  {
    // '123' --> '1234'
    return Token::NATURAL_NUMBER;
  }
  else if((state == Token::ZERO || state == Token::NATURAL_NUMBER) && c == '.')
  {
    // '123' --> '123.'
    return Token::NUMBER_WITH_TRAILING_POINT;
  }
  else if((state == Token::NUMBER_WITH_TRAILING_POINT || state == Token::DECIMAL_NUMBER) && isdigit(c))
  {
    // '123.' --> '123.4'
    return Token::DECIMAL_NUMBER;
  }
  else if((state == Token::ZERO || state == Token::NATURAL_NUMBER || state == Token::DECIMAL_NUMBER) && (c == 'e' || c == 'E'))
  {
    // 123 --> 123e
    // 123.4 --> 123.4e
    return Token::NUMBER_WITH_TRAILING_E;
  }
  else if(state == Token::NUMBER_WITH_TRAILING_E && (c == '+' || c == '-'))
  {
    // 123.4 --> 123.4e-
    return Token::NUMBER_WITH_TRAILING_E_SIGN;
  }
  else if((state == Token::NUMBER_WITH_TRAILING_E || state == Token::NUMBER_WITH_TRAILING_E_SIGN) && isdigit(c) && c != 0)
  {
    // 123.4e- --> 123.4e-1
    return Token::NUMBER;
  }
  else if(state == Token::NUMBER && isdigit(c))
  {
    // 123.4e-1 --> 123.4e-12
    return Token::NUMBER;
  }
  else if((state == Token::NIL || state == Token::IDENTIFIER) && isid(c))
  {
    return Token::IDENTIFIER;
  }
  else if(state == Token::NIL && c == '#')
  {
    return Token::HASH;
  }
  else if(state == Token::HASH && (c == 't' || c == 'f'))
  {
    return Token::BOOLEAN;
  }
  else if(state == Token::NIL && (c == '(' || c == '['))
  {
    return Token::OPEN_PAREN;
  }
  else if(state == Token::NIL && (c == ')' || c == ']'))
  {
    return Token::CLOSE_PAREN;
  }
  else if((state == Token::NIL || state == Token::WHITESPACE) && isspace(c))
  {
    return Token::WHITESPACE;
  }
  else if(state == Token::NIL && c == ';')
  {
    return Token::COMMENT;
  }
  else if(state == Token::COMMENT && c != '\n')
  {
    return Token::COMMENT;
  }
  else
  {
    return Token::NIL;
  }
}

bool Scanner::eof(void)
{
  return this->stream.eof();
}

bool isid(int c)
{
  return
    isalnum(c) ||
    c == '+' || c == '-' || c == '*' || c == '/' ||
    c == '%' || c == '!' || c == '<' || c == '>';
}

bool Token::acceptable(void)
{
  return this->type > Token::NIL;
}

std::string Token::description(void)
{
  return descriptions.find(this->type)->second;
}

}
