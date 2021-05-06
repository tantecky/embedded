#include <Arduino.h>

#include "Bands.hpp"
#include "Analyzer.hpp"
constexpr float Bands::Freqs[];

void Bands::fill(const float *const freqs, const float *const mags)
{
    memset(values, 0, sizeof(values));
    size_t lastMatch = 0;

    for (size_t i = 0; i < Analyzer::SampleCountHalf1; i++)
    {
        const float freq = freqs[i];
        const float mag = mags[i];

        for (size_t idx = lastMatch; idx < Count; idx++)
        {
            if (Freqs[idx] >= freq)
            {
                values[idx] += mag;
                lastMatch = idx;
                break;
            }
        }
    }
}

void Bands::print() const
{
    for (size_t i = 0; i < Bands::Count; i++)
    {
        Serial.printf("%d %f\n", i, values[i]);
    }
}