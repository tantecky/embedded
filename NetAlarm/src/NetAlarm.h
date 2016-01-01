#ifndef NETALARM_H_KQRYVERN
#define NETALARM_H_KQRYVERN
#include <Arduino.h>
#include <EthernetUdp.h>

#include "PacketTypes.h"
#include "PacketWriter.h"
#include "PacketReader.h"

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
        const long retriggerInterval,
        const byte *mac, const IPAddress ip, const int localPort,
        const IPAddress dnsServer, const IPAddress gateway);

    void arm();
    void disarm();
    void init();
    void checkForMotion();
    uint32_t id() const { return id_; }
    void sendPacket(byte remoteIp[4], PacketType packetType);
    void blinkRedLed(int n, int duration = 100);
    void blinkGreenLed(int n, int duration = 100);
    void beep(int n, int duration = 100);
    void sendOverUdp(IPAddress remoteIp, int remotePort, PacketType packet);

  private:
    static const int PIN_PIR = 8;
    static const int PIN_PIEZO = 6;
    static const int PIN_RED_LED = 7;
    static const int PIN_GREEN_LED = 5;

    const uint32_t id_;
    func_t onArmed_;
    func_t onDisarmed_;
    func_t onTriggered_;
    bool armed_;
    const long retriggerInterval_;
    unsigned long lastTrigger_;
    EthernetUDP udpClient_;
    byte mac_[6];
    const IPAddress ip_;
    const int localPort_;
    PacketWriter packetWriter_;
    PacketReader packetReader_;
    const IPAddress dnsServer_;
    const IPAddress gateway_;

    void blinkLed_(int pin, int n, int duration = 100);
    bool intervalLapsed_();
    void trigger_();

};


#endif /* end of include guard: NETALARM_H_KQRYVERN */

