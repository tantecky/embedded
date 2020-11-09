#ifndef DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81
#define DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81

#include <stdint.h>
#include "actor.hpp"
#include "sensor.hpp"
#include "usb.hpp"

template <typename T>
class Pid
{
private:
    Actor<T> &actor_;
    Sensor &sensor_;
    const float kp_;
    const float ki_;
    const float kd_;
    float prevError_;
    uint32_t prevTicks_;
    float iError_;

public:
    Pid(Actor<T> &actor, Sensor &sensor,
        const float kp, const float ki = 0, const float kd = 0) : actor_(actor),
                                                                  sensor_(sensor),
                                                                  kp_(kp),
                                                                  ki_(ki),
                                                                  kd_(kd),
                                                                  prevError_(0),
                                                                  prevTicks_(),
                                                                  iError_(0)
    {
    }

    inline void reset()
    {
        prevError_ = 0;
        prevTicks_ = HAL_GetTick();
        iError_ = 0;
    }

    inline const T getMinValue() const { return actor_.getMinValue(); }
    inline const T getMaxValue() const { return actor_.getMaxValue(); }

    void update(const float target)
    {
        const float error = target - sensor_.getValue();

        float output = kp_ * error;

        const uint32_t dt = HAL_GetTick() - prevTicks_;

        if (dt > 0)
        {
            iError_ += error * dt;
            output += ki_ * iError_;
            output += kd_ * (error - prevError_) / dt;
        }

#pragma GCC diagnostic ignored "-Wdouble-promotion"
        Serial.printf("ERR: %.3f DT: %u OUT: %.3f\r\n", error, dt, output);
        // Serial.printf("Stack3 %u\r\n", uxTaskGetStackHighWaterMark(nullptr));
#pragma GCC diagnostic pop

        if (output > getMaxValue())
        {
            output = getMaxValue();
        }
        else if (output < getMinValue())
        {
            output = getMinValue();
        }

        prevError_ = error;
        prevTicks_ = HAL_GetTick();

        actor_.setValue(static_cast<T>(output));
    };
};

#endif /* DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81 */
