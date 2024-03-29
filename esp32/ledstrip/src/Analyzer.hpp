#ifndef E69F620B_0204_468D_A730_DAD5D3C63FF7
#define E69F620B_0204_468D_A730_DAD5D3C63FF7

#include <Arduino.h>
#include <driver/i2s.h>
#include <type_traits>
#include <algorithm>
#include <iterator>

#include "SinCosTable.hpp"
#include "Bands.hpp"
#include "Utils.hpp"

class Analyzer
{
public:
    static constexpr int SampleCount = 1024;
    static constexpr int M = log2(SampleCount);
    static constexpr int SampleCountHalf = SampleCount / 2;
    static constexpr int SampleCountHalf1 = SampleCountHalf + 1;
    static constexpr float NoiseFloor = 0;
    static constexpr float AmplitudeFactor = 0.2f;

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
    uint8_t i2sData[bytesPerRead];
    float *audioBuffer = nullptr;
    float *freqs = nullptr;
    const float *window = nullptr;
    Bands bands;

    inline const auto maxIdx() const
    {
        return std::distance(audioBuffer,
                             std::max_element(audioBuffer, audioBuffer + SampleCountHalf1));
    }

    const float *createHann(const int n)
    {
        // n + 1 because non-symmetric window
        const int n1 = n + 1;
        float *w = new float[n1];

        for (size_t i = 0; i < n1; i++)
        {
            w[i] = 0.5f - 0.5f * cosf((2.0f * M_PI_F * i) / n);
        }

        return w;
    }

    void applyWindow()
    {
        for (size_t i = 0; i < SampleCount; i++)
        {
            audioBuffer[i] *= window[i];
        }
    }

public:
    Analyzer()
    {
    }

    void setup();

    // returns `true` when data changed
    bool read();

    inline const Bands &getBands() const { return bands; }

    inline const float maxMag() const
    {
        return audioBuffer[maxIdx()];
    }

    inline const float maxFreq() const
    {
        return freqs[maxIdx()];
    }
};

#endif /* E69F620B_0204_468D_A730_DAD5D3C63FF7 */
