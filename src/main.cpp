
// Some Digisparks have a built-in LED on pin 0, while some have it on pin 1.
#define PinLEDInternal 0

#include <sleep.h>

void pingInternalLED(uint8_t flashes, int delayMs)
{
  for (int i = flashes; i > 0; i--)
  {
    digitalWrite(PinLEDInternal, HIGH);
    delay(delayMs);
    digitalWrite(PinLEDInternal, LOW);
    if (i > 1) delay(delayMs);
  }
}

void setup()
{
  pinMode(PinLEDInternal, OUTPUT);

  pingInternalLED(2, 300);
}

void loop()
{
  pingInternalLED(2, 700);
  delay(2000);
}
