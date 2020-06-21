#ifdef __AVR_ATtiny85__
#define SCALER (8000000L / F_CPU)
const int PIN = 1;
#else
const int PIN = 11;
#endif

void setup()
{
  pinMode(PIN, OUTPUT);
}

void loop()
{
  // 4 kHz for 50 ms
  tone(PIN, 4000 / SCALER, 50 * SCALER);
  delay(1500 * SCALER);
}
