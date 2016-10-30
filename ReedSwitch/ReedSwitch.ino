#include <limits.h>

const int LED = 7; // or LED_BUILTIN
const int REED = 8;
const int PIN_PIEZO = 6;
const unsigned long ALARM_DELAY = 10000;
unsigned long whenDisconnected = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(REED, INPUT);
}

inline bool isConnected()
{
  return digitalRead(REED) == HIGH ? true : false;
}

void loop()
{
  if (!isConnected()) {
    digitalWrite(LED, HIGH);

    if (whenDisconnected == 0) {
      whenDisconnected = millis();
    } else {
      unsigned long now = millis();
      unsigned long diff;

      if (whenDisconnected > now) {
        diff = ULONG_MAX - whenDisconnected + now;
      } else {
        diff = now - whenDisconnected;
      }

      if (diff > ALARM_DELAY) {
        while (!isConnected()) {
          analogWrite(PIN_PIEZO, 230);
          delay(100);
          analogWrite(PIN_PIEZO, 0);
          delay(100);
        }
        digitalWrite(LED, LOW);
        whenDisconnected = 0;
      }
    }
  } else {
    digitalWrite(LED, LOW);
    whenDisconnected = 0;
  }

  delay(50);
}
