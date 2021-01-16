#include <Arduino.h>
#include <TM1637Display.h>

// CLK, DIO
TM1637Display display(D6, D7);

void setup()
{
}

void loop()
{

  uint8_t dots = 0b11100000;
  display.setBrightness(0);

  display.showNumberDecEx(1253, dots, false);
  delay(10000);

  display.setBrightness(7);
  display.showNumberDecEx(1253, dots, false);

  delay(10000);
}
