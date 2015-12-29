#include <Arduino.h>
#include "NetAlarm.h"
#include "Packets.h"

NetAlarm::NetAlarm(uint32_t id, 
    func_t onArmed, func_t onDisarmed, func_t onTriggered,
    long retriggerInterval, int blinksOnArmDisarm,
    int beepsOnTrigger):
  id_(id), 
  onArmed_(onArmed), onDisarmed_(onDisarmed), onTriggered_(onTriggered),
  armed_(false), 
  retriggerInterval_(retriggerInterval), 
  blinksOnArmDisarm_(blinksOnArmDisarm), beepsOnTrigger_(beepsOnTrigger)
{
}

void NetAlarm::init()
{
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);

  arm();
}

void NetAlarm::checkForMotion()
{
  if (armed_ && intervalLapsed_() && digitalRead(PIN_PIR) == HIGH) {
    trigger_();
  }

  onTriggered_();

  // just a little break
  delay(10);
}

void NetAlarm::arm()
{
  if (armed_)
    return;

  armed_ = true;
  blinkLed_(PIN_RED_LED, blinksOnArmDisarm_);
  lastTrigger_ = millis();

  onArmed_();
}

void NetAlarm::disarm()
{
  if (!armed_)
    return;

  armed_ = false;
  blinkLed_(PIN_GREEN_LED, blinksOnArmDisarm_);

  onDisarmed_();
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
  beep_(beepsOnTrigger_);
  lastTrigger_ = millis();
}

void NetAlarm::blinkLed_(int pin, int n, int duration)
{
  if(n < 1)
    return;

  for (int i = 0; i < n; ++i) {
    digitalWrite(pin, HIGH); 
    delay(duration);    
    digitalWrite(pin, LOW);
    delay(duration);
  }
}

void NetAlarm::beep_(int n, int duration)
{
  if(n < 1)
    return;

  for (int i = 0; i < n; ++i) {
    analogWrite(PIN_PIEZO, 20); 
    delay(duration);    
    analogWrite(PIN_PIEZO, 0);
    delay(duration);
  }
}
