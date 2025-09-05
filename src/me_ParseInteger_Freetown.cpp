// Free functions for [me_ParseInteger]

/*
  Author: Martin Eden
  Last mod.: 2025-09-05
*/

#include <me_ParseInteger.h>

#include <me_BaseTypes.h>

using namespace me_ParseInteger;

/*
  Multiply by 10 if it won't overflow
*/
TBool Freetown::SafeMulBy10(
  TUint_2 * Result
)
{
  const TUint_2 MaxValue = TUint_2_Max / 10;

  if (*Result > MaxValue)
    return false;

  *Result = *Result * 10;

  return true;
}

/*
  Sum two numbers if they will not overflow
*/
TBool Freetown::SafeAdd(
  TUint_2 * Result,
  TUint_2 Value
)
{
  TUint_2 MaxValue = TUint_2_Max - Value;

  if (*Result > MaxValue)
    return false;

  *Result = *Result + Value;

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
  2024 # # #
  2025-09-05
*/
