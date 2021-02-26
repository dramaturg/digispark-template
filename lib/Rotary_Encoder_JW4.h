/*  roto_jw4.ino -- JW, 29 September 2015 -- 
 *  A 4-state state-machine implementation of rotary
 *  encoding for KY-040 rotary knobs.  The state-machine picture at
 *  https://e2e.ti.com/support/microcontrollers/hercules/f/312/t/318762
 *  in a Feb 4, 2014 7:40 PM post by Anthony Seely shows counts
 *  increasing on transitions 10 -> 11 -> 01 -> 00 -> 10 and
 *  decreasing on transitions the other way.  Transitions between 00
 *  and 11 or 10 and 01 are invalid.  This code detects valid
 *  transitions by (abOld xor abNew) equaling 1 or 2.  It detects
 *  up-count events by the tri-bit value ABA' (where A' is the new
 *  reading on pin A) being equal to 1, 2, 5, or 6 (a bit mask of
 *  0x66), and down-count events by ABA' being equal to 0, 3, 4, or 7
 *  (a bit mask of 0x99).
 *
 *  On a KY-040 unit I tested, there are 30 detent positions per turn.
 *  With this unit the code generates 60 counts per turn, which can be
 *  seen individually as one turns the rotor slowly.  Odd counts
 *  appear between detents, even counts at detents.
 *
 *  Set quadrature-signal pin numbers, via PinA and PinB constants.
 *  Set IPINMODE to INPUT_PULLUP if there are no external pull-ups
 *  on encoder AB pins, else set IPINMODE to INPUT
 */

#include <EnableInterrupt.h>

//enum { PinA=2, PinB=3, IPINMODE=INPUT_PULLUP };

static  byte abOld;          // Initialize state
volatile int encoderNewPos;  // current rotary count
         int encoderPos;     // old rotary count

// On interrupt, read input pins, compute new state, and adjust count
void pinChangeISR()
{
  enum { upMask = 0x66, downMask = 0x99 };
  byte abNew = (digitalRead(PinA) << 1) | digitalRead(PinB);
  byte criterion = abNew^abOld;

  if (criterion==1 || criterion==2) {
    if (upMask & (1 << (2*abOld + abNew/2)))
      encoderNewPos++;
    else encoderNewPos--;       // upMask = ~downMask
  }

  abOld = abNew;        // Save new state
}

inline void rotaryEncoderSetup()
{
  pinMode(PinA, IPINMODE);
  pinMode(PinB, IPINMODE);
  enableInterrupt(PinA, pinChangeISR, CHANGE); // Set up pin-change interrupts
  enableInterrupt(PinB, pinChangeISR, CHANGE);

  abOld = encoderNewPos = encoderPos = 0;
}

inline void rotaryEncoderTick()
{
  if (encoderPos != encoderNewPos) {
    encoderPos = encoderNewPos;
  }
}
