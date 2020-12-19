#ifndef BE77698B_FED8_4C43_A2C4_9364AB859DF2
#define BE77698B_FED8_4C43_A2C4_9364AB859DF2

#include <Arduino.h>

class Remote
{
private:
    static byte channel;

    static void read433(byte *data);

public:
    static float temperature;

    static void setup(const int8_t pin, const byte channel);
};

#endif /* BE77698B_FED8_4C43_A2C4_9364AB859DF2 */
