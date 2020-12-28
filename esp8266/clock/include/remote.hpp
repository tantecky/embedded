#ifndef BE77698B_FED8_4C43_A2C4_9364AB859DF2
#define BE77698B_FED8_4C43_A2C4_9364AB859DF2

#include <Arduino.h>

#include "SensorReceiver.h"

class Remote
{
private:
    static int8_t pin;
    static byte channel;

    static void read433(byte *data);

public:
    static float temperature;

    static void setup(const int8_t pin_, const byte channel);

    inline static void enable()
    {
        SensorReceiver::init(digitalPinToInterrupt(Remote::pin), Remote::read433);
    }

    inline static void disable()
    {
        detachInterrupt(digitalPinToInterrupt(Remote::pin));
    }
};

#endif /* BE77698B_FED8_4C43_A2C4_9364AB859DF2 */
