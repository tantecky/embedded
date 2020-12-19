#include "remote.hpp"
#include "SensorReceiver.h"

byte Remote::channel = 0xFF;
float Remote::temperature = NAN;

void Remote::setup(const int8_t pin, const byte channel)
{
    Remote::channel = channel;

    SensorReceiver::init(digitalPinToInterrupt(pin), Remote::read433);
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