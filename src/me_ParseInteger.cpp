// Parse ASCII to integer (uint2 or int2)

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include <me_ParseInteger.h>

#include <me_BaseTypes.h>
#include <me_StreamsCollection.h>

using namespace me_ParseInteger;

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
  TUint_2 * Result,
  TAddressSegment DataSeg
)
{
  const TUint_1 NumericBase = 10;

  me_StreamsCollection::TWorkmemInputStream DataStream;
  TUnit Byte;
  TUint_1 Digit;
  TUint_2 Value;

  if (!DataStream.Init(DataSeg))
    return false;

  Value = 0;

  while (DataStream.Read(&Byte))
  {
    if (!Freetown::ToDigit(&Digit, Byte))
      return false;

    if (!Freetown::SafeMul(&Value, Value, NumericBase))
      return false;

    if (!Freetown::SafeAdd(&Value, Value, Digit))
      return false;
  }

  *Result = Value;

  return true;
}

/*
  Parse ASCII data to integer in range -32768 .. 32767.

  Details

    ASCII integer MAY start with "-".

  Examples

    "1" -> 1
    "-1" -> -1
    "--1" -> false
    "+1" -> false
    "0" -> 0
    "-0" -> 0
*/
TBool me_ParseInteger::AsciiToSint2(
  TSint_2 * ValuePtr,
  TAddressSegment DataSeg
)
{
  const TUint_2
    MaxPosValue = 0x7FFF, // 32767
    MaxNegValue = 0x8000; // 32768

  me_StreamsCollection::TWorkmemInputStream DataStream;
  TUnit FirstByte;
  TBool IsNegative;
  TUint_2 Ui2Value;
  TBool IsConverted;

  if (!DataStream.Init(DataSeg))
    return false;

  if (!DataStream.Read(&FirstByte))
    return false;

  IsNegative = (FirstByte == '-');

  if (IsNegative)
  {
    // Advance data segment past minus sign:
    ++DataSeg.Addr;
    --DataSeg.Size;
  }

  IsConverted = AsciiToUint2(&Ui2Value, DataSeg);

  if (!IsConverted)
    return false;

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
  2024 # # # #
  2025-08-26
*/
