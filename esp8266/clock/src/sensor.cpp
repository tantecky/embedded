#include "main.hpp"
#include "sensor.hpp"

void Sensor::setup()
{

    while (!bme_.begin())
    {
        Serial.println("Could not find BME280I2C sensor!");
        delay(1000);
    }
}

void Sensor::tick()
{
    bme_.read(presIn_, tempIn_, humIn_,
              BME280::TempUnit(BME280::TempUnit_Celsius),
              BME280::PresUnit(BME280::PresUnit_Pa));

    // calibration
    tempIn_ -= 0.7f;

    Oled.clearBuffer();                    // clear the internal memory
    Oled.setFont(u8g2_font_logisoso16_tr); // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall

    String text = "IN:";
    text += String(tempIn_, '\x001');
    text += " ";
    text += String(humIn_, '\x000');
    text += "%";

    Oled.drawStr(0, 16, text.c_str());

    Oled.sendBuffer();
    delay(5000);
}