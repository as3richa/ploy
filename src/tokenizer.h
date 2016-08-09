#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include "tracked_stream.h"

namespace ploy
{

class Token
{
public:
  enum Type
  {
    ZERO = -999,
    NATURAL_NUMBER,
    NUMBER_WITH_TRAILING_POINT,
    DECIMAL_NUMBER,
    NUMBER_WITH_TRAILING_E,
    NUMBER_WITH_TRAILING_E_SIGN,
    HASH,
    NIL = 0,

    WHITESPACE,
    COMMENT,
    OPEN_PAREN,
    CLOSE_PAREN,
    IF,
    LET,
    LAMBDA,
    AND,
    OR,
    CONS,
    NUMBER,
    IDENTIFIER,
    BOOLEAN,
    N_TYPES
  };

  int line;
  int column;

  Type type;
  std::string lexeme;

  Token(void) : line(-1), column(-1) { ; }
  Token(int line_, int column_) : line(line_), column(column_)
  {
    type = NIL;
    lexeme = "";
  }

  bool acceptable(void);
  std::string description(void);
};

class Scanner
{
private:
  Token previous;
  bool unscanned;
  bool spaced;

  Token scanAny(void);

public:
  TrackedStream stream;

  Scanner(std::istream& input) : previous(-1, -1), unscanned(false), spaced(true), stream(input) { ; }

  Token scan(void);
  void unscan(void);
  bool eof(void);
};

}

#endif