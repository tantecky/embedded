#include "main.hpp"
#include "sensor.hpp"
#include "remote.hpp"

void Sensor::setup()
{
    while (!bme_.begin())
    {
        Serial.println("Could not find BME280I2C sensor!");
        delay(1000);
    }

    lastDrawn_ = millis();
}

void Sensor::tick()
{
    if ((millis() - lastDrawn_) < 20000)
    {
        return;
    }

    bme_.read(presIn_, tempIn_, humIn_,
              BME280::TempUnit(BME280::TempUnit_Celsius),
              BME280::PresUnit(BME280::PresUnit_Pa));

    // calibration
    tempIn_ -= 0.7f;

    Oled.clearBuffer();                    // clear the internal memory
    Oled.setFont(u8g2_font_logisoso16_tr); // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    setContrast();

    String text = "in:";
    text += String(tempIn_, '\x001');
    text += "  ";
    text += String(humIn_, '\x000');
    text += "%";

    Oled.drawStr(centerOffset(text), 16, text.c_str());

    if (!isnan(Remote::temperature))
    {
        String text2 = "out:";
        text2 += String(Remote::temperature, '\x001');
        Oled.drawStr(centerOffset(text2), 32, text2.c_str());
    }

    Oled.sendBuffer();

    lastDrawn_ = millis();

    do
    {
        yield();
    } while ((millis() - lastDrawn_) < 5000);
}