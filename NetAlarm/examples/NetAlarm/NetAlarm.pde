#include <NetAlarm.h>

// change this to your unique id
uint32_t id = 0;
NetAlarm alarm(id);

void setup() 
{
  alarm.init();
}

void loop() 
{
  alarm.checkForMotion();
}
