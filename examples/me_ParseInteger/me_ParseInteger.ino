// [me_ParseInteger] test/demo

/*
  Enter random space/newline separated strings to Serial.

  Entities that fall into range -32768 .. 32767 are converted to
  integers.

    "  143 1a la" -> (143) '1a'? 'la'?
    "0 -0 +0 --0" -> (0) (0) '+0'? '--0'?
    "000123 0000123 00000123" -> (123) '0000123'? '0000012'?
    "32767 32768" -> (32767) '32768'?
    "-32768 -32769" -> (-32768) '-32769'?

  Under the hood there is also ToUint2() function if you wish
  range 0 .. 65535.
*/

/*
  Author: Martin Eden
  Last mod.: 2024-05-23
*/

#include <me_ParseInteger.h>
#include <me_SerialTokenizer.h>
#include <me_MemorySegment.h>

#include <me_InstallStandardStreams.h>
#include <me_UartSpeeds.h>
#include <me_BaseTypes.h>

// Forwards:
void GetEntityDemo();

void setup()
{
  Serial.begin(me_UartSpeeds::Arduino_Normal_Bps);
  Serial.setTimeout(10);
  InstallStandardStreams();

  printf("[me_ParseInteger] Okay, we are here.\n");

  printf("\n");
  printf("We will parse integers from -32768 to 32767.\n");
  printf("Enter something...\n");

  while (true)
  {
    GetEntityDemo();
  }
}

void loop()
{
}

using namespace me_ParseInteger;
// using namespace me_SerialTokenizer;
// using namespace me_MemorySegment;
using namespace me_BaseTypes;

// Forwards:
void PrintSeg(TMemorySegment Segment);

/*
  Get entity from serial input.

  Try to parse it to integer in range [-32768, 32767].
*/
void GetEntityDemo()
{
  const TUint_2 BufferSize = 8;

  TUint_1 Buffer[BufferSize];

  TMemorySegment BufferSeg =
    {
      .Start = { .Bytes = Buffer },
      .Size = sizeof(Buffer),
    };

  me_SerialTokenizer::TCapturedEntity Capture;

  if (me_SerialTokenizer::GetEntity(&Capture, BufferSeg))
  {
    if (Capture.IsTrimmed)
    {
      printf("'");
      PrintSeg(Capture.Segment);
      printf("'..?\n");
      return;
    }

    TSint_2 Int2;

    if (!AsciiToSint2(&Int2, Capture.Segment))
    {
      printf("'");
      PrintSeg(Capture.Segment);
      printf("'?\n");
      return;
    }

    printf("(%d)\n", Int2);
  }
}

/*
  Print uncooked contents of memory segment to stdout.
*/
void PrintSeg(me_MemorySegment::TMemorySegment Segment)
{
  const TUint_1 ElementSize = 1;
  FILE * OutputStream = stdout;

  fwrite(
    Segment.Start.Bytes,
    Segment.Size,
    ElementSize,
    OutputStream
  );
}

/*
  2024-05-08
  2024-05-13
*/
