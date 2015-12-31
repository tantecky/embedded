#include <string.h>        
#include <SPI.h>        
#include <Ethernet.h>

#include "NetAlarm.h"

NetAlarm::NetAlarm(const uint32_t id, 
    func_t onArmed, func_t onDisarmed, func_t onTriggered,
    const long retriggerInterval,
    const byte *mac, const IPAddress ip, const int localPort):
  id_(id), 
  onArmed_(onArmed), onDisarmed_(onDisarmed), onTriggered_(onTriggered),
  armed_(false),
  retriggerInterval_(retriggerInterval),
  ip_(ip), localPort_(localPort),
  packetWriter_(*this), packetReader_(*this)
{
  memcpy(mac_, mac, sizeof(mac_));
}

void NetAlarm::init()
{
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);

  Ethernet.begin(mac_, ip_); 
  udpClient_.begin(localPort_);

  arm();
}

void NetAlarm::checkForMotion()
{
  if (armed_ && intervalLapsed_() && digitalRead(PIN_PIR) == HIGH) {
    trigger_();
  }

  int packetSize = udpClient_.parsePacket();
  if(packetSize > 0)
  {
    udpClient_.read(packetReader_.receiveBuffer(), 
        PacketReader::MAX_RX_PACKET_SIZE);

    packetReader_.processPacket(packetSize);
  }

  // just a little break
  delay(10);
}

void NetAlarm::arm()
{
  if (armed_)
    return;

  armed_ = true;
  lastTrigger_ = millis();

  onArmed_();
}

void NetAlarm::disarm()
{
  if (!armed_)
    return;

  armed_ = false;

  onDisarmed_();
}

void NetAlarm::blinkRedLed(int n, int duration)
{
  blinkLed_(PIN_RED_LED, n, duration);
}

void NetAlarm::blinkGreenLed(int n, int duration)
{
  blinkLed_(PIN_GREEN_LED, n, duration);
}

void NetAlarm::sendOverUdp(IPAddress remoteIp, int remotePort, 
    PacketType packetType)
{
  packetWriter_.writePacket(packetType);
  udpClient_.beginPacket(remoteIp, remotePort);
  udpClient_.write(packetWriter_.packet(), packetWriter_.size());
  udpClient_.endPacket();
}

void NetAlarm::beep(int n, int duration)
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
  lastTrigger_ = millis();
  onTriggered_();
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
