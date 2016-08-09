#include "parser.h"

#include <cassert>
#include <istream>
#include <list>
#include <memory>

#include "exceptions.h"
#include "tokenizer.h"
#include "tree.h"

namespace ploy
{

TreePointer parse(Scanner& scanner);
Token scanWithExpectations(Scanner&, Token::Type, Token::Type other = Token::NIL, std::string message = "");

TreePointer parse(std::istream& input)
{
  Scanner scanner(input);
  auto result = parse(scanner);
  if(!scanner.eof())
    throw ParseError(scanner.scan(), "end of file");

  return result;
}

TreePointer parse(Scanner& scanner)
{
  Token token = scanner.scan();

  switch(token.type)
  {
  case Token::OPEN_PAREN:
  {
    Token function_or_operation = scanner.scan();
    switch(function_or_operation.type)
    {
      case Token::LET:
      {
        std::list<std::pair<std::string, TreePointer>> bindings;

        scanWithExpectations(scanner, Token::OPEN_PAREN, Token::NIL, "parenthesized list of identifier/value bindings");

        Token peek;
        for(;;)
        {
          peek = scanWithExpectations(scanner, Token::OPEN_PAREN, Token::CLOSE_PAREN, "identifier/value binding pair");
          if(peek.type == Token::CLOSE_PAREN)
            break;

          peek = scanWithExpectations(scanner, Token::IDENTIFIER);

          TreePointer value = parse(scanner);
          bindings.push_back(std::make_pair(peek.lexeme, value));

          scanWithExpectations(scanner, Token::CLOSE_PAREN);
        }

        TreePointer body = parse(scanner);

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::Let(bindings, body);
      }
      case Token::LAMBDA:
      {
        std::list<std::string> identifiers;

        scanWithExpectations(scanner, Token::OPEN_PAREN, Token::NIL, "parenthesized identifier list");

        Token peek;

        for(;;)
        {
          peek = scanWithExpectations(scanner, Token::IDENTIFIER, Token::CLOSE_PAREN, "identifier");
          if(peek.type == Token::CLOSE_PAREN)
            break;

          identifiers.push_back(peek.lexeme);
        }

        TreePointer body = parse(scanner);

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::Lambda(identifiers, body);
      }
      case Token::CLOSE_PAREN:
        throw ParseError(token, "at least one expression between open and close parentheses/brackets");
      default:
      {
        TreePointer fn;
        if(
          function_or_operation.type != Token::AND &&
          function_or_operation.type != Token::OR &&
          function_or_operation.type != Token::CONS
        )
        {
          scanner.unscan();
          fn = parse(scanner);
        }

        std::list<TreePointer> params;
        for(;;)
        {
          Token peek = scanner.scan();
          if(peek.type == Token::CLOSE_PAREN)
            break;

          scanner.unscan();
          params.push_back(parse(scanner));
        }

        switch(function_or_operation.type)
        {
        case Token::AND:
          return new Tree::And(params);
        case Token::OR:
          return new Tree::Or(params);
        case Token::CONS:
          if(params.size() != 2)
            throw ParseError(function_or_operation, "exactly two parameters to cons");
          return new Tree::Cons(*params.begin(), *++params.begin());
        default:
          return new Tree::Application(fn, params);
        }
      }
    }
  }
  case Token::NUMBER:
    return new Tree::Number(token.lexeme);
  case Token::IDENTIFIER:
    return new Tree::Identifier(token.lexeme);
  case Token::BOOLEAN:
    return new Tree::Boolean(token.lexeme);
  default:
    throw ParseError(token, "expression");
  }
}

Token scanWithExpectations(Scanner& scanner, Token::Type type, Token::Type other, std::string message)
{
  if(message == "")
  {
    Token desired;
    desired.type = type;
    message = desired.description();

    if(other != Token::NIL)
    {
      desired.type = other;
      message += " or ";
      message += desired.description();
    }
  }

  if(scanner.eof())
    throw ParseError(scanner.stream.line, scanner.stream.column, message);

  Token token = scanner.scan();
  if(token.type != type && token.type != other)
    throw ParseError(token, message);

  return token;
}

}
