// Demo of [me_InstallStandardStreams]

/*
  InstallStandardStreams();
  ..
  printf("Yeah baby!\n");
*/

/*
  Author: Martin Eden
  Last mod.: 2024-10-28
*/

#include <me_InstallStandardStreams.h>
#include <me_BaseTypes.h>

void setup()
{
  Serial.begin(57600);

  RunTest();
}

void loop()
{
}

// --

void RunTest()
{
  InstallStandardStreams();

  printf("[me_InstallStandardStreams] Just testing output via printf().\n");
  delay(10);
  printf("%lu milliseconds passed\n", millis());
  printf("[me_InstallStandardStreams] Done.\n");
}

/*
  2024-05-19
  2024-10-28
*/
