// Parse ASCII to integer value

/*
  Author: Martin Eden
  Last mod.: 2024-05-23
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_ParseInteger
{
  using me_MemorySegment::TMemorySegment;

  // 0 .. 65535
  TBool AsciiToUint2(
    TUint_2 * ValuePtr,
    TMemorySegment DataSeg
  );

  // -32768 .. 32767
  TBool AsciiToSint2(
    TSint_2 * ValuePtr,
    TMemorySegment DataSeg
  );

  // Implementation

  // Char to 0 .. 9
  TBool ToDigit(TUint_1 * Digit, TChar Char);
}

/*
  2024-05-13
  2024-05-23 using memory segment
*/
