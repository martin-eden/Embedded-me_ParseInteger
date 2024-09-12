// Parse ASCII to integer (uint2 or int2)

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

#include "me_ParseInteger.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

// Forwards:
TBool SafeAdd(TUint_2 * Result, TUint_2 Base, TUint_1 Digit);
TBool SafeMul(TUint_2 * Result, TUint_2 Base, TUint_1 Digit);

/*
  Parse ASCII data to integer in range 0 .. 65535.

  Parameters

    <@ ValuePtr: u2> - Output. Memory address to store integer.
    <DataSeg> - Input. Structure describing memory segment with data.
      Address and length.

  Returns

    true - data value is parsed and stored as integer

  Details

    Leading zeroes are allowed: "001" -> 1

    Non-digits are not allowed: (" 1", "1,") -> nah

    Exceeding range is not allowed: "99999" -> nah
*/
TBool me_ParseInteger::AsciiToUint2(
  TUint_2 * ValuePtr,
  TMemorySegment DataSeg
)
{
  if (DataSeg.Size == 0)
    return false;

  TUint_2 Value = 0;

  TUint_1 Offset = 0;

  TUint_1 Byte;
  while (DataSeg.GetByte(&Byte, Offset))
  {
    // Non-digit character - return
    TUint_1 Digit;
    if (!ToDigit(&Digit, Byte))
      return false;

    // Do (Value = Value * 10 + Digit) without overflow or return
    {
      TUint_2 NewValue = Value;

      // Case like (Value: 9999)
      const TUint_1 NumericBase = 10;
      if (!SafeMul(&NewValue, NewValue, NumericBase))
        return false;

      // Case like (Value: 65530, Digit: 6)
      if (!SafeAdd(&NewValue, NewValue, Digit))
        return false;

      Value = NewValue;
    }

    // Advance pointer
    ++Offset;
  }

  // store value
  *ValuePtr = Value;

  return true;
}

const TUint_2 MaxUi2 = 0xFFFF;

/*
  Multiply two numbers if they will not overflow.
*/
TBool SafeMul(TUint_2 * Result, TUint_2 Base, TUint_1 Digit)
{
  // Invariant of "Base * Digit > MaxUi2"
  if (Base > MaxUi2 / Digit)
    return false;

  *Result = Base * Digit;

  return true;
}

/*
  Sum two numbers and if they will not overflow.
*/
TBool SafeAdd(TUint_2 * Result, TUint_2 Base, TUint_1 Digit)
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
TBool me_ParseInteger::ToDigit(TUint_1 * Digit, TChar Char)
{
  if (!((Char >= '0') && (Char <= '9')))
    return false;

  *Digit = Char - '0';

  return true;
}

/*
  Parse ASCII data to integer in range -32768 .. 32767.

  Details

    "-1" -> -1
    "-0" -> 0
    "--1" -> nah
*/
TBool me_ParseInteger::AsciiToSint2(
  TSint_2 * ValuePtr,
  TMemorySegment DataSeg
)
{
  if (DataSeg.Size == 0)
    return false;

  TBool IsNegative;

  IsNegative = (DataSeg.Bytes[0] == '-');

  if (IsNegative)
  {
    // Advance data segment past minus sign:
    ++DataSeg.Start.Addr;
    --DataSeg.Size;
  }

  TUint_2 Ui2Value;
  TBool IsConverted;

  IsConverted = AsciiToUint2(&Ui2Value, DataSeg);

  if (!IsConverted)
    return false;

  const TUint_2 MaxPosValue = (0xFFFF >> 1); // 32767
  const TUint_2 MaxNegValue = MaxPosValue + 1; // 32768

  if (IsNegative)
  {
    if (Ui2Value > MaxNegValue)
      return false;
  }
  else // if positive
  {
    if (Ui2Value > MaxPosValue)
      return false;
  }

  *ValuePtr = Ui2Value;
  if (IsNegative)
    *ValuePtr = -(*ValuePtr);

  return true;
}

/*
  2024-05-13
  2024-05-23 memory segment, safe mul, safe add
  2024-06-29 sync with libs
*/
