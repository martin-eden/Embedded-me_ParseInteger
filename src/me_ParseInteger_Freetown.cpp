// Free functions for [me_ParseInteger]

/*
  Author: Martin Eden
  Last mod.: 2024-12-20
*/

#include <me_ParseInteger.h>

using namespace me_ParseInteger;

const TUint_2 MaxUi2 = 0xFFFF;

/*
  Multiply two numbers if they will not overflow
*/
TBool Freetown::SafeMul(
  TUint_2 * Result,
  TUint_2 Base,
  TUint_1 Digit
)
{
  // Invariant of "Base * Digit > MaxUi2"
  if (Base > MaxUi2 / Digit)
    return false;

  *Result = Base * Digit;

  return true;
}

/*
  Sum two numbers if they will not overflow
*/
TBool Freetown::SafeAdd(
  TUint_2 * Result,
  TUint_2 Base,
  TUint_1 Digit
)
{
  // Invariant of "Base + Digit > MaxUi2"
  if (Base > MaxUi2 - Digit)
    return false;

  *Result = Base + Digit;

  return true;
}

/*
  Convert "0" .. "9" ASCII character to 0 .. 9.

  Returns

    false - when character is not digit

  Note

    Yes I know implementation is trivial but I need function
    in this form for design.
*/
TBool Freetown::ToDigit(
  TUint_1 * Digit,
  TUint_1 Char
)
{
  if (!((Char >= '0') && (Char <= '9')))
    return false;

  *Digit = Char - '0';

  return true;
}

/*
  2024-05-23 memory segment, safe mul, safe add
  2024-06-29 sync with libs
  2024-10-05 Freetown
*/
