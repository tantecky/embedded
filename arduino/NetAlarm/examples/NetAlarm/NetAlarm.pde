#include <NetAlarm.h>

//---CUSTOM SETTINGS - START

// ID of your NetAlarm - CHANGE THIS
const uint32_t id = 0xDEADBEEF;

// code for a 433 MHz remote switch, which arms alaram - CHANGE THIS
// has to be 24 bit long at the maximum
// used when remoteControl is true (see below)
const unsigned long remoteArmCode = 112233;

// code for a 433 MHz remote switch, which disarms alaram - CHANGE THIS
// has to be 24 bit long at the maximum
// used when remoteControl is true (see below)
const unsigned long remoteDisarmCode = 445566;

// Arduino's MAC - CHANGE THIS
// you can use following generator
// https://www.hellion.org.uk/cgi-bin/randmac.pl
const byte mac[] = {
  0x76, 0x2E, 0xc9, 0x0E, 0x65, 0x62
};

// Arduino's IP - CHANGE THIS
const IPAddress ip(192, 168, 0, 2);

// where to send UDP datagrams - CHANGE THIS
const IPAddress remoteIp(192, 168, 0, 1);

// DNS server - CHANGE THIS
const IPAddress dnsServer(192, 168, 0, 3);

// gateway address - CHANGE THIS
const IPAddress gateway(192, 168, 0, 4);

// set to true, if you want to be able arm/disarm alarm over network (UDP)
const bool networkControl = true;
// set to true, if you want to be able arm/disarm alarm
// over 433 MHz with a remote control
const bool remoteControl = true;
// minimal time interval in milliseconds beetwen alarm triggers
const long retriggerInterval = 60000;
// arm on power on
const bool armOnPowerOn = true;
// port which Arduino listens on
const int localPort = 1337;
// port which remote machine listens on
const int remotePort = 1337;

//---CUSTOM SETTINGS - END

NetAlarm alarm(id, &onArmed, &onDisarmed, &onTriggered,
    retriggerInterval, mac, ip, localPort, dnsServer, gateway,
    remoteControl, remoteArmCode, remoteDisarmCode);

void setup()
{
  alarm.init();
  if (armOnPowerOn) {
    alarm.arm();
  }
}

void loop()
{
  alarm.checkForMotion();

  if (networkControl) {
    alarm.checkForIncomingPackets();
  }

  if (remoteControl) {
    alarm.checkForRemoteControl();
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
