#ifndef DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81
#define DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81

#include "actor.hpp"
#include "sensor.hpp"

template <typename T>
class Pid
{
private:
    /* data */
public:
    Pid(const Actor<T> &actor, const Sensor &sensor,
        const float kp, const float ki = 0, const float kd = 0)
    {
    }
};

#endif /* DB5DAA6B_E806_4EBE_ACAA_CB06436A6D81 */
