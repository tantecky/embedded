#include <Arduino.h>
#include <driver/i2s.h>
#include <type_traits>
#include "Analyzer.hpp"
#include "SinCosTable.hpp"
#include "rfft.hpp"

Analyzer analyzer;

SinCosTable SinCos(Analyzer::SampleCount, Analyzer::M);

TaskHandle_t writerTaskHandle;

// Task to write samples to our server
void writerTask(void *param)
{
  while (true)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
  }
}

void setup()
{
  Serial.begin(115200);

  SinCos.init();
  analyzer.setup();

  // xTaskCreatePinnedToCore(writerTask, "writerTask", 4096, NULL, 1, &writerTaskHandle, 0);
}

// ARDUINO_RUNNING_CORE 1
// xTaskCreateUniversal(loopTask, "loopTask", 8192, NULL, 1, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);
void loop()
{
  analyzer.read();
}