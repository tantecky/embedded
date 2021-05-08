#ifndef ADEC6C15_56E6_4B4D_AC8D_3CC85AF95362
#define ADEC6C15_56E6_4B4D_AC8D_3CC85AF95362

#include "FastLED.h"
#include "Bands.hpp"

template <int ledCount, int pin>
class LedDriver
{
private:
    static constexpr int ledsPerBand = ledCount / Bands::Count;

    CLEDController &controller;
    CRGB leds[ledCount];

public:
    LedDriver() : controller(FastLED.addLeds<WS2812B, pin>(leds, ledCount))
    {
    }

    void setup()
    {
        controller.setCorrection(LEDColorCorrection::TypicalLEDStrip);
    }

    void update(const Bands &bands)
    {
        for (size_t i = 0; i < Bands::Count; i++)
        {
            // const uint8_t mag = uint8_t(bands.getValue(i) * 255);
        }

        fill_rainbow(leds, ledCount, 0, 1);
    }
};

#endif /* ADEC6C15_56E6_4B4D_AC8D_3CC85AF95362 */
