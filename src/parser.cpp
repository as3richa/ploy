#include "parser.h"

#include <cassert>
#include <istream>
#include <vector>
#include <memory>

#include <iostream>

#include "exceptions.h"
#include "tokenizer.h"
#include "tree.h"

namespace ploy
{

const Tree* parse(Scanner& scanner);
Token scanWithExpectations(Scanner&, Token::Type, Token::Type other = Token::NIL, std::string message = "");

std::vector<const Tree*> parse(std::istream& input)
{
  Scanner scanner(input);
  std::vector<const Tree*> expressions;

  while(!scanner.eof())
  {
    expressions.push_back(parse(scanner));
  }

  return expressions;
}

const Tree* parse(Scanner& scanner)
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
        std::vector<std::pair<std::string, const Tree*>> bindings;

        scanWithExpectations(scanner, Token::OPEN_PAREN, Token::NIL, "parenthesized list of identifier/value bindings");

        Token peek;
        for(;;)
        {
          peek = scanWithExpectations(scanner, Token::OPEN_PAREN, Token::CLOSE_PAREN, "identifier/value binding pair");
          if(peek.type == Token::CLOSE_PAREN)
            break;

          peek = scanWithExpectations(scanner, Token::IDENTIFIER);

          const Tree* value = parse(scanner);
          bindings.push_back(std::make_pair(peek.lexeme, value));

          scanWithExpectations(scanner, Token::CLOSE_PAREN);
        }

        const Tree* body = parse(scanner);

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::Let(bindings, body);
      }
      case Token::LAMBDA:
      {
        std::vector<std::string> identifiers;

        scanWithExpectations(scanner, Token::OPEN_PAREN, Token::NIL, "parenthesized identifier list");

        Token peek;

        for(;;)
        {
          peek = scanWithExpectations(scanner, Token::IDENTIFIER, Token::CLOSE_PAREN, "identifier");
          if(peek.type == Token::CLOSE_PAREN)
            break;

          identifiers.push_back(peek.lexeme);
        }

        const Tree* body = parse(scanner);

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::Lambda(identifiers, body);
      }
      case Token::DEFINE:
      {
        Token identifier = scanWithExpectations(scanner, Token::IDENTIFIER);
        const Tree* body = parse(scanner);

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::Definition(identifier.lexeme, body);
      }
      case Token::IF:
      {
        const Tree* conditional = parse(scanner);
        const Tree* true_branch = parse(scanner);
        const Tree* false_branch = parse(scanner);

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::If(conditional, true_branch, false_branch);
      }
      case Token::COND:
      {
        std::vector<std::pair<const Tree*, const Tree*>> branches;
        const Tree* else_branch;

        for(;;)
        {
          auto peek = scanWithExpectations(scanner, Token::OPEN_PAREN, Token::CLOSE_PAREN, "parenthesized conditional/expression pair");
          if(peek.type == Token::CLOSE_PAREN)
          {
            throw ParseError(scanner.stream.line, scanner.stream.column, "missing else branch in cond");
          }

          peek = scanner.scan();
          if(peek.type == Token::ELSE)
          {
            else_branch = parse(scanner);
            scanWithExpectations(scanner, Token::CLOSE_PAREN);
            break;
          }
          else
          {
            scanner.unscan();

            branches.push_back(std::make_pair(parse(scanner), parse(scanner)));
            scanWithExpectations(scanner, Token::CLOSE_PAREN);
          }
        }

        scanWithExpectations(scanner, Token::CLOSE_PAREN);

        return new Tree::Cond(branches, else_branch);
      }
      case Token::ELSE:
        throw ParseError(token, "expression");
      case Token::CLOSE_PAREN:
        throw ParseError(token, "at least one expression between open and close parentheses/brackets");
      default:
      {
        const Tree* fn;
        if(
          function_or_operation.type != Token::AND &&
          function_or_operation.type != Token::OR
        )
        {
          scanner.unscan();
          fn = parse(scanner);
        }

        std::vector<const Tree*> params;
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
