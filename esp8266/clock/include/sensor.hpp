#ifndef ECEDF7E5_C22D_48C0_909E_7CE8EC062DA7
#define ECEDF7E5_C22D_48C0_909E_7CE8EC062DA7

#include <BME280I2C.h>

class Sensor_
{
private:
    BME280I2C::Settings settings_;
    BME280I2C bme_;

    float presIn_;
    float tempIn_;
    float humIn_;

    unsigned long lastDrawn_;

public:
    Sensor_() : settings_(
                    BME280::OSR_X16,
                    BME280::OSR_X16,
                    BME280::OSR_X16,
                    BME280::Mode_Normal,
                    BME280::StandbyTime_500us,
                    BME280::Filter_16,
                    BME280::SpiEnable_False,
                    BME280I2C::I2CAddr_0x76),
                bme_(settings_),
                presIn_(NAN), tempIn_(NAN), humIn_(NAN)
    {
    }

    void setup();
    void tick();

    const float inline pressure() { return presIn_; }
    const float inline temperature() { return tempIn_; }
    const float inline humidity() { return humIn_; }
};

extern Sensor_ Sensor;

#endif /* ECEDF7E5_C22D_48C0_909E_7CE8EC062DA7 */
