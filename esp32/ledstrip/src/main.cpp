#include <Arduino.h>
#include <arduinoFFT.h>
#include <driver/i2s.h>

// size of sample
#define SAMPLES 1024
constexpr i2s_port_t I2S_PORT = I2S_NUM_0;
constexpr int BLOCK_SIZE = SAMPLES;
constexpr int BUF_COUNT = 16;

void setup()
{
  Serial.begin(115200);
  Serial.println("Configuring I2S...");
  esp_err_t err;
  // The I2S config as per the example
  const i2s_config_t i2s_config = {
      .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive, not transfer
      // .sample_rate = 44100,                              // 44 kHz
      .sample_rate = 16000,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // for old esp-idf versions use RIGHT
      .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Interrupt level 1
      .dma_buf_count = BUF_COUNT,               // number of buffers
      .dma_buf_len = BLOCK_SIZE,                // samples per buffer
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0};
  // The pin config as per the setup
  const i2s_pin_config_t pin_config = {
      .bck_io_num = 16,   // SCK - IO16
      .ws_io_num = 17,    // WS - IO17
      .data_out_num = -1, // not used (only for speakers)
      .data_in_num = 32   // SD - IO32
  };
  // Configuring the I2S driver and pins.
  // This function must be called before any I2S driver read/write operations.
  err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  if (err != ESP_OK)
  {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true)
      ;
  }
  err = i2s_set_pin(I2S_PORT, &pin_config);
  if (err != ESP_OK)
  {
    Serial.printf("Failed setting pin: %d\n", err);
    while (true)
      ;
  }
  Serial.println("I2S driver installed.");
  delay(5000);
}

void loop()
{
  static uint8_t i2sData[BLOCK_SIZE];
  // Read multiple samples at once and calculate the sound pressure
  size_t num_bytes_read;
  esp_err_t err = i2s_read(I2S_PORT,
                           i2sData,
                           BLOCK_SIZE, // the doc says bytes, but its elements.
                           &num_bytes_read,
                           portMAX_DELAY); // no timeout

  // Serial.println(num_bytes_read);
  // Serial.printf("%X\n", samples[0]);
  // Serial.printf("%d\n", samples[0]);

  if (err == ESP_OK)
  {
    // Serial.write(i2sData, num_bytes_read);
    int32_t *samples = (int32_t *)i2sData;
    for (size_t i = 0; i < num_bytes_read / 4; i++)
    {
      int32_t sample = (samples[i] >> 11);
      // int16_t sample = samples[i];
      // Serial.write(uint8_t((sample >> 24) & 0xFF));
      // Serial.write(uint8_t((sample >> 16) & 0xFF));
      Serial.write(uint8_t((sample >> 8) & 0xFF));
      Serial.write(uint8_t(sample & 0xFF));

      // Serial.println(sample);

      //     /* code */
      // Serial.write(samples[i] >> 11);
      // Serial.printf("%X\n", samples[i] >> 11);
      // Serial.printf("%X\n", samples[i]);
    }
  }
}
