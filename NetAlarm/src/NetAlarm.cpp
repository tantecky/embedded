#include "NetAlarm.h"

NetAlarm::NetAlarm(uint32_t id, long retriggerInterval, int numberOfBlinks,
    int numberOfBeeps):
  id_(id), armed_(false), retriggerInterval_(retriggerInterval), 
  numberOfBlinks_(numberOfBlinks), numberOfBeeps_(numberOfBeeps)
{
}

void NetAlarm::init()
{
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);
  // wait for PIR initialization
  delay(INIT_DELAY);
  arm();
}

void NetAlarm::checkForMotion()
{
  if (armed_ && intervalLapsed_() && digitalRead(PIN_PIR) == HIGH) {
    trigger_();
  }

  // just a little break
  delay(20);
}

void NetAlarm::arm()
{
  if (armed_)
    return;

  armed_ = true;
  blinkLed_(PIN_RED_LED, numberOfBlinks_);
  lastTrigger_ = millis();
}

void NetAlarm::disarm()
{
  if (!armed_)
    return;

  armed_ = false;
  blinkLed_(PIN_GREEN_LED, numberOfBlinks_);
}

bool NetAlarm::intervalLapsed_()
{
  long diff = millis() - lastTrigger_;

  // overflow handling 
  if (diff < 0) {
    lastTrigger_ = millis() - retriggerInterval_;
    return false;
  }
  else if (diff < retriggerInterval_) {
    return false;
  }
  else {
    return true;
  }
}

void NetAlarm::trigger_()
{
  beep_(numberOfBeeps_);
  lastTrigger_ = millis();
}

void NetAlarm::blinkLed_(int pin, int n, int duration)
{
  for (int i = 0; i < n; ++i) {
    digitalWrite(pin, HIGH); 
    delay(duration);    
    digitalWrite(pin, LOW);
    delay(duration);
  }
}

void NetAlarm::beep_(int n, int duration)
{
  for (int i = 0; i < n; ++i) {
    analogWrite(PIN_PIEZO, 20); 
    delay(duration);    
    analogWrite(PIN_PIEZO, 0);
    delay(duration);
  }
}
