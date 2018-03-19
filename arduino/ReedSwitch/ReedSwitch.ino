#include <limits.h>

const int LED = 4; // or LED_BUILTIN
const int REED = 6;
const int PIN_PIEZO = 3;
const unsigned long ALARM_DELAY = 60000;
unsigned long whenDisconnected = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(REED, INPUT_PULLUP);
}

inline bool isConnected()
{
  return digitalRead(REED) == HIGH ? false : true;
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
