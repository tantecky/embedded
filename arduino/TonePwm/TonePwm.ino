#include <avr/sleep.h>

#define SCALER (8000000L / F_CPU)
const int PIEZO = 1;
const int WAKE = 2;
const int BTN = 3;

volatile bool shouldSleep = true;

ISR(PCINT0_vect)
{
  // HIGH == connected to Vcc
  if (digitalRead(WAKE) == HIGH)
  {
    shouldSleep = false;
  }

  // LOW == connected to GND
  if (digitalRead(BTN) == LOW)
  {
    shouldSleep = true;
  }
}

void enterSleep()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here

  sleep_enable(); // enables the sleep bit in the mcucr register
                  // so sleep is possible. just a safety pin

  sleep_mode(); // here the device is actually put to sleep!!
                // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  sleep_disable(); // first thing after waking from sleep:
                   // disable sleep...
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
  GIMSK = 0b00100000;
  PCMSK = 0b00001100;
  sei();
}

void loop()
{
  // 4 kHz for 50 ms
  tone(PIEZO, 4000 / SCALER, 50 * SCALER);
  delay(1000 * SCALER);

  if (shouldSleep)
  {
    enterSleep();
  }
}
