#ifndef DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81
#define DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81

#include <stdint.h>
#include "actor.hpp"
#include "sensor.hpp"

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
                                                                  prevTicks_(0),
                                                                  iError_(0)
    {
    }

    inline void reset()
    {
        prevError_ = 0;
        prevTicks_ = 0;
        iError_ = 0;
    }

    inline const T getMinValue() const { return actor_.getMinValue(); }
    inline const T getMaxValue() const { return actor_.getMaxValue(); }

    void update(const float target);
};

#endif /* DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81 */
