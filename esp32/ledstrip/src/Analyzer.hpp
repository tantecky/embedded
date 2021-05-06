#ifndef E69F620B_0204_468D_A730_DAD5D3C63FF7
#define E69F620B_0204_468D_A730_DAD5D3C63FF7

#include <Arduino.h>
#include <driver/i2s.h>
#include <type_traits>

#include "Utils.hpp"

class Analyzer
{
public:
    static constexpr int SampleCount = 1024;
    static constexpr int M = log2(SampleCount);

private:
    static constexpr int bytesPerRead = 512;
    static constexpr int samplingRate = 44100;

    static_assert(bytesPerRead <= 512, "out of range");
    static_assert(SampleCount >= bytesPerRead, "out of range");

    static_assert(isPowerof2(SampleCount), "has to be power of 2");
    static_assert(isPowerof2(bytesPerRead), "has to be power of 2");

    static const i2s_config_t i2sConfig;
    static const i2s_pin_config_t i2sPins;
    static constexpr i2s_port_t i2sPort = I2S_NUM_1;

    int bufferTip = 0;
    float *audioBuffer = nullptr;

public:
    Analyzer()
    {
    }

    void setup();
    void read();
};

#endif /* E69F620B_0204_468D_A730_DAD5D3C63FF7 */
