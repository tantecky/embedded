#include <avr/wdt.h>
#include <avr/sleep.h>

#define SCALER (8000000L / F_CPU)
const int PIEZO = 1;
const int WAKE = 2;
const int BTN = 3;
const int RX = 4;

volatile bool signalArrived = false;

ISR(PCINT0_vect)
{
  // HIGH == connected to Vcc
  if (digitalRead(WAKE) == HIGH)
  {
    signalArrived = true;
  }

  // LOW == connected to GND
  if (digitalRead(BTN) == LOW)
  {
    signalArrived = false;
  }
}

ISR(WDT_vect)
{
}

void enterSleep(const uint8_t duration)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here

  sleep_enable(); // enables the sleep bit in the mcucr register
                  // so sleep is possible. just a safety pin

  wdt_enable(duration);
  // wdt tiggers interrupt on time out
  WDTCR |= (1 << WDIE);

  sleep_mode(); // here the device is actually put to sleep!!
                // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

  sleep_disable(); // first thing after waking from sleep:
                   // disable sleep...
  wdt_disable();
}

void setup()
{
  wdt_disable();

  // to save power
  pinMode(0, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  pinMode(PIEZO, OUTPUT);
  pinMode(WAKE, INPUT);
  pinMode(BTN, INPUT_PULLUP);

  pinMode(RX, OUTPUT);
  // RX disabled
  digitalWrite(RX, LOW);

  ADCSRA &= ~(1 << ADEN); // disable ADC
  GIMSK = 0b00100000;
  PCMSK = 0b00001100;

  sei();

  // 4 kHz for 50 ms
  tone(PIEZO, 4000 / SCALER, 50 * SCALER);
  delay(250 * SCALER);
  tone(PIEZO, 4000 / SCALER, 50 * SCALER);
  delay(250 * SCALER);
}

void loop()
{
  // RX enabled
  digitalWrite(RX, HIGH);
  enterSleep(WDTO_60MS);
  // RX disabled
  digitalWrite(RX, LOW);

  while (signalArrived)
  {
    tone(PIEZO, 4000 / SCALER, 50 * SCALER);
    delay(1000 * SCALER);
  }

  enterSleep(WDTO_500MS);
}
