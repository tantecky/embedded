#include <Arduino.h>

#include "Bands.hpp"
#include "Analyzer.hpp"

constexpr float Bands::Freqs[];

void Bands::normalize()
{
    for (size_t i = 0; i < Bands::Count; i++)
    {
        values[i] *= Analyzer::AmplitudeNorm;

        if (values[i] > 1)
        {
            values[i] = 1.0f;
        }
    }
}

void Bands::fill(const float *const freqs, const float *const mags)
{

    memset(values, 0, sizeof(values));
    size_t lastMatch = 0;

    for (size_t i = 0; i < Analyzer::SampleCountHalf1; i++)
    {
        const float mag = mags[i];

        if (mag <= Analyzer::NoiseFloor)
        {
            continue;
        }

        const float freq = freqs[i];
        constexpr int Count1 = Count - 1;

        if (lastMatch == 0 && freq < Freqs[0])
        {
            continue;
        }
        else if (lastMatch > 0 && freq > Freqs[Count1])
        {
            values[Count1] += mag;
        }

        for (size_t idx = lastMatch; idx < Count1; idx++)
        {
            if (freq >= Freqs[idx] && freq < Freqs[idx + 1])
            {
                values[idx] += mag;
                lastMatch = idx;
                break;
            }
        }
    }

    normalize();
}

void Bands::print() const
{
    Serial.println("++++");

    for (size_t i = 0; i < Bands::Count; i++)
    {
        Serial.printf("%d %d %f\n", i, int(Freqs[i]), values[i]);
    }

    Serial.println("----");
}