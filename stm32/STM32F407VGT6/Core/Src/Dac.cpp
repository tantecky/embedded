#include "dac.hpp"

void Dac::init(const uint16_t initValue)
{

    HAL_DAC_Init(handle_);
    HAL_DAC_Start(handle_, channel_);
    setValue(initValue);
}

void Dac::setValue(const uint16_t value)
{

    if (value < minValue_)
    {
        value_ = minValue_;
    }
    else if (value > maxValue_)
    {
        value_ = maxValue_;
    }
    else
    {
        value_ = value;
    }

    HAL_DAC_SetValue(handle_, channel_, DAC_ALIGN_12B_R, value_);
}