
#include <EnableInterrupt.h>
#include <avr/sleep.h>

uint8_t sleepWakeUpPin;

void wakeUpFromPin()
{
    sleep_disable();
    disableInterrupt(sleepWakeUpPin);
}

void goSleepUntilPin(uint8_t pin)
{
    sleepWakeUpPin = pin;

    // preparation
    sleep_enable();
    enableInterrupt(pin, wakeUpFromPin, CHANGE);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // sleep until interrupt
    sleep_cpu();

    // executed when waking up
}
