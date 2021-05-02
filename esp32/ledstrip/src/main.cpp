#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <driver/i2s.h>
#include "secret.hpp"

// replace this with your machines IP Address
#define I2S_SERVER_URL "http://192.168.168.2:5003/samples"

constexpr size_t SampleCount = 512;
constexpr size_t BufferSampleCapacity = 30 * SampleCount;
size_t BufferTip = 0;

float *WifiBuffer = nullptr;
float *AudioBuffer = nullptr;

WiFiClient *wifiClientI2S = nullptr;
HTTPClient *httpClientI2S = nullptr;
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
    .dma_buf_len = SampleCount,
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

// send data to a remote address
void sendData(WiFiClient *wifiClient, HTTPClient *httpClient, const char *url, uint8_t *bytes, size_t count)
{
  // send them off to the server
  digitalWrite(2, HIGH);
  httpClient->begin(*wifiClient, url);
  httpClient->addHeader("content-type", "application/octet-stream");
  httpClient->POST(bytes, count);
  httpClient->end();
  digitalWrite(2, LOW);
}

// Task to write samples to our server
void writerTask(void *param)
{
  while (true)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    constexpr size_t toSend = sizeof(float) * BufferSampleCapacity;
    sendData(wifiClientI2S, httpClientI2S, I2S_SERVER_URL, (uint8_t *)WifiBuffer, toSend);
  }
}

void setup()
{
  Serial.begin(115200);
  // init FPU
  Serial.println(float(millis()) + 1337.0f);

  AudioBuffer = new float[BufferSampleCapacity];
  WifiBuffer = new float[BufferSampleCapacity];

  // launch WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  Serial.println("Started up");
  // indicator LED
  pinMode(2, OUTPUT);
  // setup the HTTP Client

  wifiClientI2S = new WiFiClient();
  httpClientI2S = new HTTPClient();

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

  xTaskCreatePinnedToCore(writerTask, "writerTask", 4096, NULL, 1, &writerTaskHandle, 1);
}

void loop()
{
  size_t bytesRead = 0;
  static uint8_t i2sData[SampleCount];

  i2s_read(i2sPort, i2sData, SampleCount, &bytesRead, portMAX_DELAY); //10 tu bylo

  if (bytesRead == SampleCount)
  {

    int32_t *p = (int32_t *)i2sData;

    // 4 because of 32-bit sampling
    const int samplesReceived = bytesRead / 4;
    // const auto a = ESP.getCycleCount();
    for (size_t i = 0; i < samplesReceived; i++)
    {
      // >> 8 because a mic is 24 bit
      // >> 4 to reduce volume

      AudioBuffer[BufferTip] = float(p[i] >> 12);
      BufferTip++;
    }
    // const auto b = ESP.getCycleCount();
    // Serial.println(b - a);

    if (BufferTip == BufferSampleCapacity)
    {
      auto temp = WifiBuffer;
      WifiBuffer = AudioBuffer;
      AudioBuffer = temp;
      BufferTip = 0;
      xTaskNotifyGive(writerTaskHandle);
    }
  }

  // Serial.println(bytesRead);
}