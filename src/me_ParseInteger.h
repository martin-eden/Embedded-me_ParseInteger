// Parse ASCII to integer value

/*
  Author: Martin Eden
  Last mod.: 2024-10-05
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_ParseInteger
{
  // Parse decimal from range [0, 65535]
  TBool AsciiToUint2(
    TUint_2 * Value,
    me_MemorySegment::TMemorySegment Data
  );

  // Parse decimal from range [-32768, +32767]
  TBool AsciiToSint2(
    TSint_2 * Value,
    me_MemorySegment::TMemorySegment Data
  );

  namespace Freetown
  {
    // Multiply two numbers if they will not overflow
    TBool SafeMul(TUint_2 * Result, TUint_2 Base, TUint_1 Digit);

    // Sum two numbers if they will not overflow
    TBool SafeAdd(TUint_2 * Result, TUint_2 Base, TUint_1 Digit);

    // Convert "0" .. "9" ASCII character to 0 .. 9
    TBool ToDigit(TUint_1 * Digit, TChar Char);
  }
}

/*
  2024-05-13
  2024-05-23 using memory segment
  2024-10-05 Interface cleanup
*/
