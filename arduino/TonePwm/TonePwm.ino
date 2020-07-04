#include <avr/sleep.h>

#define SCALER (8000000L / F_CPU)
const int PIEZO = 1;
const int WAKE = 2;
const int BTN = 3;

void wakeUpNow()
{
}

void enterSleep()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here

  sleep_enable(); // enables the sleep bit in the mcucr register
                  // so sleep is possible. just a safety pin

  /* Now it is time to enable an interrupt. We do it here so an
     * accidentally pushed interrupt button doesn't interrupt
     * our running program. if you want to be able to run
     * interrupt code besides the sleep function, place it in
     * setup() for example.
     *
     * In the function call attachInterrupt(A, B, C)
     * A   can be either 0 or 1 for interrupts on pin 2 or 3.
     *
     * B   Name of a function you want to execute at interrupt for A.
     *
     * C   Trigger mode of the interrupt pin. can be:
     *             LOW        a low level triggers
     *             CHANGE     a change in level triggers
     *             RISING     a rising edge of a level triggers
     *             FALLING    a falling edge of a level triggers
     *
     * In all but the IDLE sleep modes only LOW can be used.
     */

  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                      // wakeUpNow when pin 2 gets LOW

  sleep_mode(); // here the device is actually put to sleep!!
                // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  sleep_disable();    // first thing after waking from sleep:
                      // disable sleep...
  detachInterrupt(0); // disables interrupt 0 on pin 2 so the
                      // wakeUpNow code will not be executed
                      // during normal running time.s
}

void setup()
{

  // to save power
  pinMode(0, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  pinMode(PIEZO, OUTPUT);
  pinMode(WAKE, INPUT);
  pinMode(BTN, INPUT_PULLUP);

  ADCSRA &= ~(1 << ADEN); // disable ADC (before power-off)

  attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                      // wakeUpNow when pin 2 gets LOW

  tone(PIEZO, 4000 / SCALER, 50 * SCALER);
  tone(PIEZO, 4000 / SCALER, 50 * SCALER);
  delay(1500 * SCALER);

  enterSleep();
}

void loop()
{
  // 4 kHz for 50 ms
  tone(PIEZO, 4000 / SCALER, 50 * SCALER);
  delay(1000 * SCALER);

  if (digitalRead(BTN) == LOW)
  {
    enterSleep();
  }
}
