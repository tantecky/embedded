#include <stdio.h>
#include "AudioFile.h"
#include "fixtures.h"
#include "SensorReceiver.h"

const float THRESHOLD = 0.5f;
unsigned long Time = 0;

unsigned long micros()
{
  return Time;
}

void attachInterrupt(uint8_t, void (*)(void), int mode)
{
}

void process()
{

  AudioFile<float> audioFile;
  audioFile.load("./test.wav");
  // audioFile.printSummary();

  int channel = 0;
  unsigned long timeStep = 1e6 / audioFile.getSampleRate();
  // printf("timeStep: %ld\n", timeStep);

  int numSamples = audioFile.getNumSamplesPerChannel();

  for (int i = 1; i < numSamples; i++) {
    float prev = audioFile.samples[channel][i - 1];
    float current = audioFile.samples[channel][i];

    bool change = (current > THRESHOLD && prev <= THRESHOLD)
        || (current < THRESHOLD && prev >= THRESHOLD);

    if (change) {
      Time = i * timeStep;
      SensorReceiver::interruptHandler();
    }
  }
}

void showTempHumi(byte* data)
{
  // is data a ThermoHygro-device?
  if ((data[3] & 0x1f) == 0x1e) {
    // Yes!

    byte channel, randomId;
    int temp;
    short int humidity;

    // Decode the data
    SensorReceiver::decodeThermoHygro(data, channel, randomId, temp, humidity);

    // printf temperature. Note: temp is 10x the actual temperature!
    printf("Temperature: ");
    printf("%d", temp / 10); // units
    printf(".");
    printf("%d", temp % 10); // decimal
    // printf("Temp raw: %d", temp); // decimal

    // printf humidity
    printf(" deg, Humidity: ");
    printf("%d", humidity);
    printf("%% REL");

    // printf channel
    printf(", Channel: %d\n", channel);
  }
}

int main(int argc, char* argv[])
{
  // Init the receiver on interrupt pin 0 (digital pin 2).
  // Set the callback to function "showTempHumi", which is called
  // whenever valid sensor data has been received.
  SensorReceiver::init(0, showTempHumi);
  process();

  return 0;
}
