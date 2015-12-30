#include <NetAlarm.h>

//---CUSTOM SETTINGS - START
const uint32_t id = 0xDEADBEEF;

byte arduinoMac[] = {
    0xC3, 0x9F, 0xB4, 0x97, 0x0F, 0x2B
};
IPAddress arduinoIp(192, 168, 168, 1);
IPAddress remoteIp(192, 168, 168, 2);
const long retriggerInterval = 60000;
//---CUSTOM SETTINGS - END

NetAlarm alarm(id, &onArmed, &onDisarmed, &onTriggered,
    retriggerInterval);

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
  alarm.beep(5);
}
