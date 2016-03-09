/*
 * Author: Tomas Antecky
 * Created on: 2016-01-02
 */
#include <string.h>
#include <SPI.h>
#include <Ethernet.h>

#include "NetAlarm.h"
#include "Debug.h"

NetAlarm::NetAlarm(const uint32_t id,
    func_t onArmed, func_t onDisarmed, func_t onTriggered,
    const long retriggerInterval,
    const byte *mac, const IPAddress ip, const int localPort,
    const IPAddress dnsServer, const IPAddress gateway,
    const bool remoteControl,
    const unsigned long remoteArmCode,
    const unsigned long remoteDisarmCode):
  id_(id),
  onArmed_(onArmed), onDisarmed_(onDisarmed), onTriggered_(onTriggered),
  armed_(false),
  retriggerInterval_(retriggerInterval),
  ip_(ip), localPort_(localPort),
  packetWriter_(*this), packetReader_(*this),
  dnsServer_(dnsServer), gateway_(gateway),
  remoteControl_(remoteControl),
  remoteArmCode_(remoteArmCode),
  remoteDisarmCode_(remoteDisarmCode)
{
  memcpy(mac_, mac, static_cast<byte>(sizeof(mac_)));
}

void NetAlarm::init()
{
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);

  if (remoteControl_) {
     // Receiver on interrupt 0 => that is pin #2
     rcSwitch_.enableReceive(digitalPinToInterrupt(2));
  }

#ifdef NETALARM_DEBUG
  Serial.begin(9600);
#endif

  Ethernet.begin(mac_, ip_, dnsServer_, gateway_);
  udpClient_.begin(localPort_);
}

void NetAlarm::checkForMotion()
{
  if (armed_ && intervalLapsed_() && digitalRead(PIN_PIR) == HIGH) {
    trigger_();
  }
}

void NetAlarm::checkForRemoteControl()
{
  if (rcSwitch_.available()) {
    unsigned long code = rcSwitch_.getReceivedValue();

    DEBUG_PRINT(String("Received remote 433 MHz code: ") + String(code));

    if (code == remoteArmCode_) {
      arm();
    }
    else if (code == remoteDisarmCode_) {
      disarm();
    }

    rcSwitch_.resetAvailable();
  }

}

void NetAlarm::checkForIncomingPackets()
{
  int packetSize = udpClient_.parsePacket();
  if (packetSize > 0) {
     DEBUG_PRINT(String("Received UDP packet of size: ") + String(packetSize));
     udpClient_.read(packetReader_.receiveBuffer(),
        PacketReader::MAX_RX_PACKET_SIZE);

     packetReader_.processPacket(packetSize);
  }
}

void NetAlarm::arm()
{
  if (armed_)
    return;

  armed_ = true;
  lastTrigger_ = millis();
  DEBUG_PRINT("Armed");
  onArmed_();
}

void NetAlarm::disarm()
{
  if (!armed_)
    return;

  armed_ = false;
  DEBUG_PRINT("Disarmed");
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
  DEBUG_PRINT(String("Sending UDP packet type: ") + String(packetType));
  packetWriter_.writePacket(packetType);
  udpClient_.beginPacket(remoteIp, remotePort);
  udpClient_.write(packetWriter_.packet(), packetWriter_.size());
  udpClient_.endPacket();
  DEBUG_PRINT("UDP packet sent");
}

void NetAlarm::beep(int n, int duration)
{
  if(n < 1)
    return;

  for (int i = 0; i < n; ++i) {
    analogWrite(PIN_PIEZO, 230);
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
  DEBUG_PRINT("Triggered");
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
