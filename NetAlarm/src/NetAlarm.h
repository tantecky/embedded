#include <Arduino.h>

class NetAlarm
{
public:
  NetAlarm();
  void disarm();

private:
  bool armed_;
};
