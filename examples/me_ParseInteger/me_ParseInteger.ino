// [me_ParseInteger] test/demo

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

/*
  Enter random space/newline separated strings to Serial.

  Entities falling into range -32768 .. 32767 are converted to
  integers.

    "  143 1a la" -> (143) '1a'? 'la'?
    "0 -0 +0 --0" -> (0) (0) '+0'? '--0'?
    "000123 0000123 00000123" -> (123) '0000123'? '0000012'?
    "32767 32768" -> (32767) '32768'?
    "-32768 -32769" -> (-32768) '-32769'?

  Under the hood there is also ToUint2() function if you wish
  range 0 .. 65535.
*/

#include <me_ParseInteger.h>

#include <me_SerialTokenizer.h>

#include <me_BaseTypes.h>
#include <me_Console.h>

// Forwards:
void GetEntityDemo();

void setup()
{
  Console.Init();

  Console.Print("[me_ParseInteger] Okay, we are here.");

  Console.Print("");
  Console.Print("We will parse integers from -32768 to 32767.");
  Console.Print("Enter something...");

  while (true)
  {
    GetEntityDemo();
  }
}

void loop()
{
}

// Forwards:
void PrintSeg(TAddressSegment Segment);

/*
  Get entity from serial input.

  Try to parse it to integer in range [-32768, 32767].
*/
void GetEntityDemo()
{
  using
    me_SerialTokenizer::TSerialTokenizer,
    me_ParseInteger::AsciiToSint2;

  TSerialTokenizer Tokenizer;

  const TUint_2 BufferSize = 8;

  TUint_1 Buffer[BufferSize];

  TAddressSegment BufferSeg;
  BufferSeg.Size = sizeof(Buffer);
  BufferSeg.Addr = (TUint_2) Buffer;

  if (Tokenizer.GetEntity(&BufferSeg, BufferSeg))
  {
    TSint_2 Int2;

    if (!AsciiToSint2(&Int2, BufferSeg))
    {
      Console.Write("'");
      Console.Write(BufferSeg);
      Console.Write("'?");
      Console.EndLine();
      return;
    }

    Console.Write("Value (");
    Console.Print(Int2);
    Console.Write(")");
    Console.EndLine();
  }
}

/*
  2024 # # # # # # #
*/
