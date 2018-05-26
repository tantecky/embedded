#include <limits.h>
#include <ESP8266WiFi.h>

const int LED = 2; // D4
const int REED_PINS[] = { 14, 4 }; // D5, D2
const int PIN_PIEZO = 12; // D6
const unsigned long ALARM_DELAY = 60000;
unsigned long whenDisconnected = 0;

void setup()
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
  
  pinMode(LED, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);

  for (int reed : REED_PINS) {
    pinMode(reed, INPUT_PULLUP);
  }
}

inline bool isConnected()
{
  for (int reed : REED_PINS) {
    if (digitalRead(reed) == HIGH) {
      return false;
    }
  }

  return true;
}

void loop()
{
  if (!isConnected()) {
    digitalWrite(LED, LOW);

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
        digitalWrite(LED, HIGH);
        whenDisconnected = 0;
      }
    }
  } else {
    digitalWrite(LED, HIGH);
    whenDisconnected = 0;
  }

  delay(50);
}
