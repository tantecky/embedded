#include <NetAlarm.h>

// change this to your unique id
const uint32_t id = 0;

NetAlarm alarm(id, &onArmed, &onDisarmed, &onTriggered);

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
}
void onDisarmed()
{
}

void onTriggered()
{
}
