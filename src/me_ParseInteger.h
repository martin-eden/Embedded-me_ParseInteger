// Parse ASCII to integer value

/*
  Author: Martin Eden
  Last mod.: 2024-05-17
*/

#pragma once

#include <me_BaseTypes.h>

namespace me_ParseInteger
{
  using namespace me_BaseTypes;

  // 0 .. 65535
  TBool ToUint2(
    TUint_2 * ValuePtr,
    TChar * Data,
    TUint_1 DataSize
  );

  // -32768 .. 32767
  TBool ToSint2(
    TSint_2 * ValuePtr,
    TChar * Data,
    TUint_1 DataSize
  );

  // Implementation

  // Char to 0 .. 9
  TBool ToDigit(TUint_1 * Digit, TChar Char);
}

/*
  2024-05-13
*/
