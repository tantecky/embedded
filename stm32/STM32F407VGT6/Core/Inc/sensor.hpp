#ifndef B0E5A0BE_0389_4724_AB99_FF4DE66D02C3
#define B0E5A0BE_0389_4724_AB99_FF4DE66D02C3

class Sensor
{
public:
    virtual ~Sensor()
    {
    }

    virtual const float getValue() = 0;
    virtual const bool gotError() const = 0;
};



#endif /* B0E5A0BE_0389_4724_AB99_FF4DE66D02C3 */
