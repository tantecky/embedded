#include "faac.h"

const int PIN = 11;
const int REPEAT = 5;
const int REPLAY_DELAY = 5000;
const int SPAN = 15500;
const int LENGTH = sizeof(DELAYS) / sizeof(DELAYS[0]);

void setup() {
  pinMode(PIN, OUTPUT);
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

  delay(REPLAY_DELAY);
}
