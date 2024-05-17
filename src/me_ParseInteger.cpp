// Parse ASCII to integer (uint2 or int2)

/*
  Author: Martin Eden
  Last mod.: 2024-05-16
*/

#include "me_ParseInteger.h"

#include <ctype.h>

#include <me_BaseTypes.h>

using namespace me_ParseInteger;
using namespace me_BaseTypes;

/*
  Parse ASCII data to integer in range 0 .. 65535.

  Parameters

    <@ ValuePtr: u2> - Output. Memory address to store integer.
    <@ CharPtr: u1> - Input. Memory address of first character in
      ASCII buffer.
    <DataSize: u2> - Size of ASCII buffer.

  Returns

    true - data value is parsed and stored as integer

  Details

    Leading zeroes are allowed: "001" -> 1

    Non-digits are not allowed: (" 1", "1 ") -> nah

    Exceeding range is not allowed: "99999" -> nah
*/
TBool me_ParseInteger::ToUint2(
  TUint_2 * ValuePtr,
  TChar * CharPtr,
  TUint_1 DataSize
)
{
  if (DataSize == 0)
    return false;

  TUint_2 Value = 0;

  TChar* LastCharPtr = CharPtr + (DataSize - 1);

  const TUint_2 MaxValuePrefix = 0xFFFF / 10;
  const TUint_1 MaxValueSuffix = 0xFFFF % 10;

  TUint_1 Digit;
  while (CharPtr <= LastCharPtr)
  {
    if (!ToDigit(&Digit, *CharPtr))
      return false;

    // Avoid overflow without converting to larger datatype:
    if (
      (Value > MaxValuePrefix) ||
      (
        (Value == MaxValuePrefix) && (Digit > MaxValueSuffix)
      )
    )
    {
      // Case like "99999" or "65536"
      return false;
    }

    Value = Value * 10 + Digit;

    // advance pointer
    CharPtr = CharPtr + sizeof(TChar);
  }

  // store value
  *ValuePtr = Value;

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
TBool me_ParseInteger::ToDigit(TUint_1 * Digit, TChar Char)
{
  if (!isdigit(Char))
    return false;

  *Digit = Char - '0';

  return true;
}

/*
  Parse ASCII data to integer in range -32768 .. 32767.

  "+1" -> nah
  "- 1" -> nah
  "-1" -> -1
*/
TBool me_ParseInteger::ToSint2(
  TSint_2 * ValuePtr,
  TChar * CharPtr,
  TUint_1 DataSize
)
{
  if (DataSize == 0)
    return false;

  TBool IsNegative;

  IsNegative = (*CharPtr == '-');

  if (IsNegative)
  {
    // Advance data pointer past minus sign:
    CharPtr = CharPtr + sizeof(TChar);

    // Decrease data length:
    DataSize = DataSize - 1;
  }

  TUint_2 Ui2Value;
  TBool IsConverted;

  IsConverted = ToUint2(&Ui2Value, CharPtr, DataSize);

  if (!IsConverted)
    return false;

  const TUint_2 MaxPositiveValue = (0xFFFF >> 1); // 32767
  const TUint_2 MaxNegativeValue = MaxPositiveValue + 1;

  if (IsNegative && (Ui2Value > MaxNegativeValue))
    return false;

  if (!IsNegative && (Ui2Value > MaxPositiveValue))
    return false;

  *ValuePtr = Ui2Value;
  if (IsNegative)
    *ValuePtr = -*ValuePtr; // C code is so understandable!

  return true;
}

/*
  2024-05-13
*/
