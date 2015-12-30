#include <NetAlarm.h>

//---CUSTOM SETTINGS - START
const uint32_t id = 0xDEADBEEF;
const long retriggerInterval = 60000;

const byte mac[] = {
    0xC3, 0x9F, 0xB4, 0x97, 0x0F, 0x2B
};
// Arduino's IP
const IPAddress ip(192, 168, 168, 6);
// port which Arduino listens on
const int localPort = 1337;

// where to send UDP datagrams
const IPAddress remoteIp(192, 168, 168, 5);
const int remotePort = 1337;
//---CUSTOM SETTINGS - END

NetAlarm alarm(id, &onArmed, &onDisarmed, &onTriggered,
    retriggerInterval, mac, ip, localPort);

void setup() 
{
  alarm.init();
}

void loop() 
{
  alarm.checkForMotion();
}

void onArmed()
{
  alarm.blinkRedLed(10);
}
void onDisarmed()
{
  alarm.blinkGreenLed(10);
}

void onTriggered()
{
  alarm.sendOverUdp(remoteIp, remotePort, PACKET_TRIGGER);
  alarm.beep(5);
}
