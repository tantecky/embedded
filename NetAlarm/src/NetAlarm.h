#ifndef NETALARM_H_KQRYVERN
#define NETALARM_H_KQRYVERN

// prototypes for a example sketch
void onArmed();
void onDisarmed();
void onTriggered();

typedef void (*func_t)();

class NetAlarm
{
  public:
    explicit NetAlarm(const uint32_t id, 
        func_t onArmed, func_t onDisarmed, func_t onTriggered,
        const long retriggerInterval_ = 60000,
        const int blinksOnArmDisarm = 10, const int beepsOnTrigger = 5);

    void arm();
    void disarm();
    void init();
    void checkForMotion();
    uint32_t id() const { return id_; }

  private:
    static const int PIN_PIR = 8;
    static const int PIN_PIEZO = 6;
    static const int PIN_RED_LED = 7;
    static const int PIN_GREEN_LED = 5;
    static const unsigned long INIT_DELAY = 30000;

    const uint32_t id_;
    func_t onArmed_;
    func_t onDisarmed_;
    func_t onTriggered_;
    bool armed_;
    const long retriggerInterval_;
    unsigned long lastTrigger_;
    const int blinksOnArmDisarm_;
    const int beepsOnTrigger_;

    void blinkLed_(int pin, int n, int duration = 100);
    void beep_(int n, int duration = 100);
    bool intervalLapsed_();
    void trigger_();
};


#endif /* end of include guard: NETALARM_H_KQRYVERN */

