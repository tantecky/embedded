#ifndef F4525278_08F3_4EBC_B615_3BC3A700EB07
#define F4525278_08F3_4EBC_B615_3BC3A700EB07

class PressureSensor
{
public:
    virtual ~PressureSensor()
    {
    }

    virtual const float getVoltage() = 0;
    virtual const bool gotError() const = 0;
    const inline float getPressure()
    {

        return (getVoltage() - 1.f) * 0.125f * 1000 * 100;
    }
};

#endif /* F4525278_08F3_4EBC_B615_3BC3A700EB07 */
