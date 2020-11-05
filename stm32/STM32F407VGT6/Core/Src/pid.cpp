#include "pid.hpp"

template <typename T>
void Pid<T>::update(const float target)
{
    const float error = target - sensor_.getValue();
}