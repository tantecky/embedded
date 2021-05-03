#include <Arduino.h>
#include <driver/i2s.h>
#include "dft.h"

constexpr size_t BytesPerRead = 512;
constexpr size_t SampleCount = 2048;
size_t BufferTip = 0;

float *AudioBuffer = nullptr;

TaskHandle_t writerTaskHandle;

// i2s config for reading from both channels of I2S
i2s_config_t i2sConfig = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = BytesPerRead,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};

// i2s pins
i2s_pin_config_t i2sPins = {
    .bck_io_num = 16,   // SCK - IO16
    .ws_io_num = 17,    // WS - IO17
    .data_out_num = -1, // not used (only for speakers)
    .data_in_num = 32   // SD - IO323

};

i2s_port_t i2sPort = I2S_NUM_1;

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
  // init FPU
  Serial.println(float(millis()) + 1337.0f);

  AudioBuffer = new float[SampleCount];

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(10);
  digitalWrite(BUILTIN_LED, LOW);

  esp_err_t err = i2s_driver_install(i2sPort, &i2sConfig, 0, NULL);

  if (err != ESP_OK)
  {
    while (true)
    {
      Serial.printf("Failed installing driver: %d\n", err);
    }
  }

  err = i2s_set_pin(I2S_NUM_1, &i2sPins);
  if (err != ESP_OK)
  {
    while (true)
    {
      Serial.printf("Failed setting pin: %d\n", err);
    }
  }

  // ARDUINO_RUNNING_CORE 1

  // xTaskCreatePinnedToCore(writerTask, "writerTask", 4096, NULL, 1, &writerTaskHandle, 0);
}

// xTaskCreateUniversal(loopTask, "loopTask", 8192, NULL, 1, &loopTaskHandle, CONFIG_ARDUINO_RUNNING_CORE);

void loop()
{
  // const auto a = ESP.getCycleCount();
  // const auto a = micros();

  size_t bytesRead = 0;
  static uint8_t i2sData[BytesPerRead];

  i2s_read(i2sPort, i2sData, BytesPerRead, &bytesRead, portMAX_DELAY);

  if (bytesRead == BytesPerRead)
  {

    int32_t *p = (int32_t *)i2sData;

    // 4 because of 32-bit sampling
    const size_t samplesReceived = bytesRead / 4;
    for (size_t i = 0; i < samplesReceived; i++)
    {
      // >> 8 because a mic is 24 bit
      // >> 4 to reduce volume

      AudioBuffer[BufferTip] = float(p[i] >> 12);
      BufferTip++;
    }

    if (BufferTip == SampleCount)
    {
      BufferTip = 0;
      // xTaskNotifyGive(writerTaskHandle);
    }
  }

  // const auto b = ESP.getCycleCount();
  // const auto b = micros();
  // const float ms = (b - a) * (1.0f / 240000000.0f * 1000000.0f);
  // const auto us = b - a;
  // Serial.printf("%ld us\n", us);
}