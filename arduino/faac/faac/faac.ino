#include "faac.h"

#ifdef __AVR_ATtiny85__
const int PIN = 1;
#else
const int PIN = 11;
#endif
const int REPEAT = 5;
const int REPLAY_DELAY = 1000;
const int SPAN = 15500;
const int LENGTH = sizeof(DELAYS) / sizeof(DELAYS[0]);

void setup() {
  pinMode(PIN, OUTPUT);
}

void blink(int n, int duration)
{
  for(int i = 0; i < n; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(duration);
    digitalWrite(LED_BUILTIN, LOW);
    delay(duration);
  }
}

void loop() {

  for (int j = 0; j < REPEAT; j++) {
    int state = LOW;
    digitalWrite(PIN, state);

    for (int i = 0; i < LENGTH; i++) {
      state ^= 1;
      digitalWrite(PIN, state);
      delayMicroseconds(DELAYS[i]);
    }

    digitalWrite(PIN, LOW);
    delayMicroseconds(SPAN);
  }

#ifndef __AVR_ATtiny85__
  blink(1, 100);
#endif

  delay(REPLAY_DELAY);
}
