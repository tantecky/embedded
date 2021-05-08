
#include "Analyzer.hpp"
#include "rfft.hpp"

const i2s_config_t Analyzer::i2sConfig = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = samplingRate,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = bytesPerRead,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0};

const i2s_pin_config_t Analyzer::i2sPins = {
    .bck_io_num = 16,   // SCK - IO16
    .ws_io_num = 17,    // WS - IO17
    .data_out_num = -1, // not used (only for speakers)
    .data_in_num = 32   // SD - IO323

};

void Analyzer::setup()
{
    freqs = new float[SampleCountHalf1];
    window = createHann(SampleCount);

    for (size_t i = 0; i < SampleCountHalf1; i++)
    {
        constexpr float step = samplingRate / SampleCount;
        freqs[i] = step * i;
    }

    audioBuffer = new float[SampleCount];

    esp_err_t err = i2s_driver_install(i2sPort, &Analyzer::i2sConfig, 0, NULL);

    if (err != ESP_OK)
    {
        while (true)
        {
            Serial.printf("Failed installing driver: %d\n", err);
        }
    }

    err = i2s_set_pin(I2S_NUM_1, &Analyzer::i2sPins);
    if (err != ESP_OK)
    {
        while (true)
        {
            Serial.printf("Failed setting pin: %d\n", err);
        }
    }
}

bool Analyzer::read()
{
    size_t bytesRead = 0;

    i2s_read(i2sPort, i2sData, bytesPerRead, &bytesRead, portMAX_DELAY);

    if (bytesRead == bytesPerRead)
    {
        int32_t *p = (int32_t *)i2sData;

        // 4 because of 32-bit sampling
        const size_t samplesReceived = bytesRead / 4;
        for (size_t i = 0; i < samplesReceived; i++)
        {
            // >> 8 because a mic is 24 bit
            // >> 4 to reduce volume

            audioBuffer[bufferTip] = float(p[i] >> 12);
            bufferTip++;
        }

        if (bufferTip == SampleCount)
        {
            bufferTip = 0;
            applyWindow();
            // const unsigned long a = micros();
            rfft(audioBuffer, SampleCount, M);
            mag(audioBuffer, SampleCount);
            // Serial.printf("mag:%f freq:%f Hz\n", maxMag(), maxFreq());
            bands.fill(freqs, audioBuffer);
            // bands.print();
            // Serial.printf("%ld\n", micros() - a);

            return true;
        }
    }

    return false;
}
