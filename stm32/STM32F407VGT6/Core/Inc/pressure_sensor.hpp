#ifndef F4525278_08F3_4EBC_B615_3BC3A700EB07
#define F4525278_08F3_4EBC_B615_3BC3A700EB07

#include "sensor.hpp"

class PressureSensor : public Sensor
{
public:
    virtual ~PressureSensor()
    {
    }

    virtual const float getVoltage() = 0;
    const inline float getValue() override
    {
        // TODO: change to getPressure
        return getVoltage();
    }
    const inline float getPressure()
    {

        return (getVoltage() - 1.f) * 0.125f * 1000 * 100;
    }
};

#endif /* F4525278_08F3_4EBC_B615_3BC3A700EB07 */
