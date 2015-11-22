int LED = 13;
int PIR = 8;
int PIEZO = 7;

void setup() {
  pinMode(PIEZO, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  delay(60000);
  blink(5, 100);
}

void blink(int n, int duration)
{
  for(int i = 0; i < n; i++)
  {
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(duration);              // wait for a second
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    delay(duration);              // wait for a second
  }
}

void loop() {
  int state = digitalRead(PIR);
  if (state == HIGH) {
    tone(PIEZO, 200, 1000);
    blink(10, 100);
    delay(10 * 1000);
  }

  delay(100);
}
