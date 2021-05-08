#include <Arduino.h>
#include <driver/i2s.h>
#include <type_traits>
#include "LedDriver.hpp"
#include "Analyzer.hpp"
#include "SinCosTable.hpp"
#include "rfft.hpp"

Analyzer analyzer;
SinCosTable SinCos(Analyzer::SampleCount, Analyzer::M);
LedDriver<64, 22> ledDriver;

void setup()
{
  Serial.begin(115200);

  SinCos.init();
  analyzer.setup();
  ledDriver.setup();
}

// ARDUINO_RUNNING_CORE 1
// xTaskCreateUniversal(loopTask, "loopTask", 8192, NULL, 1, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
void loop()
{
  const bool changed = analyzer.read();

  if (changed)
  {
    ledDriver.update(analyzer.getBands());
  }
}