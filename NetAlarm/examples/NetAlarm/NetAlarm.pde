#include <NetAlarm.h>

//---CUSTOM SETTINGS - START

// ID of your NetAlarm - CHANGE THIS
const uint32_t id = 0xDEADBEEF;
// Arduino's MAC - CHANGE THIS
const byte mac[] = {
    0xC3, 0x9F, 0xB4, 0x97, 0x0F, 0x2B
};
// Arduino's IP - CHANGE THIS
const IPAddress ip(192, 168, 0, 2);
// where to send UDP datagrams - CHANGE THIS
const IPAddress remoteIp(192, 168, 0, 1);
// set to true, if you want to be able arm/disarm alarm over network
const bool remoteControl = true;

// minimal time interval in milliseconds beetwen alarm triggers
const long retriggerInterval = 60000;
// port which Arduino listens on
const int localPort = 1337;
// port which remote machine listens on
const int remotePort = 1337;
// set this, if you need hostname resolution
const IPAddress dnsServer = INADDR_NONE;
// set this, if you need to send pacet over the internet
const IPAddress gateway = INADDR_NONE;

//---CUSTOM SETTINGS - END

NetAlarm alarm(id, &onArmed, &onDisarmed, &onTriggered,
    retriggerInterval, mac, ip, localPort, dnsServer, gateway);

void setup()
{
  alarm.init();
}

void loop()
{
  alarm.checkForMotion();
  if (remoteControl) {
    alarm.checkForIncomingPackets();
  }

  // just a little break
  delay(10);
}

void onArmed()
{
  alarm.blinkRedLed(10);
  alarm.sendOverUdp(remoteIp, remotePort, PACKET_ARM);
}
void onDisarmed()
{
  alarm.blinkGreenLed(10);
  alarm.sendOverUdp(remoteIp, remotePort, PACKET_DISARM);
}

void onTriggered()
{
  alarm.sendOverUdp(remoteIp, remotePort, PACKET_TRIGGER);
  alarm.beep(5);
}
