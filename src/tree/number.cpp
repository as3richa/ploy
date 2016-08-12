#include "number.h"

#include <gmpxx.h>
#include <string>

#include "../exceptions.h"

namespace ploy
{

mpq_class Tree::Number::parse(std::string lexeme)
{
  size_t point_position = lexeme.find('.');
  size_t e_position = lexeme.find_first_of("eE");

  std::string integer_part = lexeme.substr(0, std::min(point_position, e_position));

  std::string fractional_part;
  if(point_position != std::string::npos)
    fractional_part = lexeme.substr(point_position + 1, e_position - point_position - 1);

  std::string exponential_part;
  if(e_position != std::string::npos)
    exponential_part = lexeme.substr(e_position + 1);
  else
    exponential_part = "0";

  mpz_class numerator = mpz_class(integer_part + fractional_part);

  mpz_class exponent = -(long)fractional_part.size();
  exponent += mpz_class(exponential_part);

  mpz_class denominator;
  if(exponent < 0)
  {
    exponent = abs(exponent);
    if(!exponent.fits_uint_p())
      throw RangeError("numeric literal is too large");

    mpz_ui_pow_ui(denominator.get_mpz_t(), 10, exponent.get_ui());
  }
  else
  {
    if(!exponent.fits_uint_p())
      throw RangeError("numeric literal is too large");

    denominator = 1;
    mpz_class multiplier;
    mpz_ui_pow_ui(multiplier.get_mpz_t(), 10, exponent.get_ui());
    numerator *= multiplier;
  }

  mpq_class result(numerator, denominator);
  result.canonicalize();

  return result;
}

std::string Tree::Number::inspect(void) const
{
  if(this->value == 0)
  {
    return "0";
  }

  mpq_class value = this->value;
  std::string result;

  if(value < 0)
  {
    result = "-";
    value = abs(value);
  }

  for(int i = 0; value != 0; i ++)
  {
    if(i == 1)
      result += '.';

    mpz_class& num = value.get_num();
    mpz_class& den = value.get_den();
    result += ((mpz_class)(num / den)).get_str();

    num %= den;
    num *= 10;

    value.canonicalize();
  }

  return result;
}

bool Tree::Number::eq(const Tree* other) const
{
  auto casted = dynamic_cast<const Tree::Number*>(other);
  return (casted && casted->value == this->value);
}

}
