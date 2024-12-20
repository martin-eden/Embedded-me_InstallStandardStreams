// Direct (stdin, stdout, stderr) to UART

/*
  Wrapped by: Martin Eden
  Last mod.: 2024-12-12
*/

#include "me_InstallStandardStreams.h"

#include <me_BaseTypes.h>
#include <me_Uart.h>

#include <stdio.h> // fdevopen(), FILE, stdin..
#include <Arduino.h> // millis()

/*
  Write char

  Docs:

    The function passed as put shall take two arguments, the first a
    character to write to the device, and the second a pointer to FILE,
    and shall return 0 if the output was successful, and a nonzero
    value if the character could not be sent to the device.
*/
TSint_2 WriteChar(
  char Char,
  FILE * File __attribute__((unused))
)
{
  me_Uart::SendByte((TUint_1) Char);

  return 1;
}

/*
  Read char

  Docs:

    The function passed as get shall take a pointer to FILE as its
    single argument, and return one character from the device, passed
    as an int type.

    If an error occurs when trying to read from the device, it shall
    return _FDEV_ERR. If an end-of-file condition was reached while
    reading from the device, _FDEV_EOF shall be returned.
*/
TSint_2 ReadChar(
  FILE * File __attribute__((unused))
)
{
  /*
    Unlike WriteChar() this functionality is not tested.
    I never used stdlib for input.
  */

  TUint_1 Byte;

  const TUint_2 AwaitTime_ms = 15;
  TUint_4 StopTime = millis() + AwaitTime_ms;

  while (true)
  {
    if (me_Uart::GetByte(&Byte))
      return (TSint_2) Byte;
    if (millis() > StopTime)
      return _FDEV_ERR;
  }
}

/*
  Assign standard streams stdin, stdout, stderr to Serial.

  Expected to be called once.

  Based on Arduino's forum answer

    https://forum.arduino.cc/t/printf-on-arduino/888528/5
*/
void InstallStandardStreams()
{
  FILE * Stream = fdevopen(&WriteChar, &ReadChar);
  /*
    fdevopen() creates stream and has side effects.

    Side effects are setting std streams to newly created stream
    (if they were not set).

    We are calling it for it's side effects but still assign
    stream to std's just in case they were set.

    Documentation found at

      https://onlinedocs.microchip.com/pr/GUID-317042D4-BCCE-4065-BB05-AC4312DBC2C4-en-US-2/index.html?GUID-9EF470A9-BEB2-4014-8FC3-5B39F3F86DAF

      https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html#gab599ddf60819df4cc993c724a83cb1a4

    (I searched for "C fdevopen".)
  */

  stdin = Stream;
  stdout = Stream;
  stderr = Stream;
}

/*
  2023-11-05
  2024-05-09
  2024-10-27 [~] Switch to [me_Uart]. Goodbye [HardwareSerial]!
  2024-11-05
*/
