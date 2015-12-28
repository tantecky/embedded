#ifndef NETALARM_H_KQRYVERN
#define NETALARM_H_KQRYVERN
#include <Arduino.h>

class NetAlarm
{
  public:
    NetAlarm(uint32_t id, long retriggerInterval_ = 60000,
        int numberOfBlinks = 10, int numberOfBeeps = 5);
    void arm();
    void disarm();
    void init();
    void checkForMotion();

  private:
    static const int PIN_PIR = 8;
    static const int PIN_PIEZO = 6;
    static const int PIN_RED_LED = 7;
    static const int PIN_GREEN_LED = 5;
    static const unsigned long INIT_DELAY = 30000;

    uint32_t id_;
    bool armed_;
    long retriggerInterval_;
    unsigned long lastTrigger_;
    int numberOfBlinks_;
    int numberOfBeeps_;

    void blinkLed_(int pin, int n, int duration = 100);
    void beep_(int n, int duration = 100);
    bool intervalLapsed_();
    void trigger_();
};


#endif /* end of include guard: NETALARM_H_KQRYVERN */

