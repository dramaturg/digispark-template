
#include <EnableInterrupt.h>
#include <avr/sleep.h>

void wakeUp(){
    sleep_disable();
    disableInterrupt(INT0);
}

void goSleep()
{
    // preparation
    sleep_enable();
    enableInterrupt(INT0, wakeUp, CHANGE);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    // sleep until interrupt
    sleep_cpu();

    // executed when waking up
}
