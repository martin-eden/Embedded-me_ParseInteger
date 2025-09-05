// Parse ASCII to integer value

/*
  Author: Martin Eden
  Last mod.: 2025-09-05
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_ParseInteger
{
  // Parse decimal from range [0, 65535]
  TBool AsciiToUint2(
    TUint_2 * Value,
    TAddressSegment Data
  );

  // Parse decimal from range [-32768, +32767]
  TBool AsciiToSint2(
    TSint_2 * Value,
    TAddressSegment Data
  );

  namespace Freetown
  {
    // Multiply by 10 if it won't overflow
    TBool SafeMulBy10(TUint_2 * Result);

    // Sum two numbers if they will not overflow
    TBool SafeAdd(TUint_2 * Result, TUint_2 Value);

    // Convert "0" .. "9" ASCII character to 0 .. 9
    TBool ToDigit(TUint_1 * Digit, TUint_1 Char);
  }
}

/*
  2024-05-13
  2024-05-23 using memory segment
  2024-10-05 Interface cleanup
  2025-09-05
*/
