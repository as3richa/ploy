#include <gmpxx.h>
#include "number.h"

namespace ploy { namespace AST {

mpq_class Number::parse(std::string lexeme)
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

  mpz_class numerator = mpz_class(integer_part + fractional_part, 10);

  mpz_class exponent = -(long)fractional_part.size();
  exponent += mpz_class(exponential_part, 10);

  mpz_class denominator;
  if(exponent < 0)
  {
    exponent = abs(exponent);
    if(!exponent.fits_uint_p())
      throw "TODO";

    mpz_ui_pow_ui(denominator.get_mpz_t(), 10, exponent.get_ui());
  }
  else
  {
    if(!exponent.fits_uint_p())
      throw "TODO";

    denominator = 1;
    mpz_class multiplier;
    mpz_ui_pow_ui(multiplier.get_mpz_t(), 10, exponent.get_ui());
    numerator *= multiplier;
  }

  mpq_class result(numerator, denominator);
  result.canonicalize();

  return result;
}

std::string Number::inspect(void) const
{
  if(this->value == 0)
  {
    return "0";
  }

  const mpq_class& value = this->value;
  const mpz_class& num = value.get_num();
  const mpz_class& den = value.get_den();

  return (den == 1) ?
    num.get_str() :
    std::string("(/ ") + num.get_str() + " " + den.get_str() + ")";
}

bool Number::eq(const Value* other) const
{
  auto casted = dynamic_cast<const Number*>(other);
  return (casted && casted->value == this->value);
}

}}
