#include "remote.hpp"
#include "SensorReceiver.h"

int8_t Remote::pin = 0;
byte Remote::channel = 0xFF;
float Remote::temperature = NAN;

void Remote::setup(const int8_t pin_, const byte channel)
{
    Remote::pin = pin_;
    Remote::channel = channel;

    SensorReceiver::enable();
}

void Remote::read433(byte *data)
{
    // is data a ThermoHygro-device?
    //  if ((data[3] & 0x1f) == 0x1e) {
    // Yes!

    byte channel, randomId;
    int temp;
    byte humidity;

    // Decode the data
    SensorReceiver::decodeThermoHygro(data, channel, randomId, temp, humidity);

    if (channel == Remote::channel)
    {
        Remote::temperature = (temp / 10) + ((temp % 10) / 10.);
    }

    // }
}