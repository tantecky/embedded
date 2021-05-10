#ifndef ADEC6C15_56E6_4B4D_AC8D_3CC85AF95362
#define ADEC6C15_56E6_4B4D_AC8D_3CC85AF95362

#include <Arduino.h>
#include "FastLED.h"
#include "Bands.hpp"

DEFINE_GRADIENT_PALETTE(palleteGradient){
    0, 0, 0, 0,
    85, 0, 0, 255,
    170, 0, 255, 0,
    255, 255, 0, 0};

static CRGBPalette16 pallete = palleteGradient;

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
        FastLED.setBrightness(55);
    }

    void update(const Bands &bands)
    {
        for (size_t i = 0; i < Bands::Count; i++)
        {
            const uint8_t mag = uint8_t(bands.getValue(i) * 255);

            for (size_t j = 0; j < ledsPerBand; j++)
            {
                const int idx = j + i * ledsPerBand;
                leds[idx] = pallete[mag];

                // Serial.println(idx);
            }
        }

        // fill_rainbow(leds, ledCount, 0, 7);

        FastLED.show();
    }
};

#endif /* ADEC6C15_56E6_4B4D_AC8D_3CC85AF95362 */
