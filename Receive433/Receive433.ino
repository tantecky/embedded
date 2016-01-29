#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
static const int PIN_PIEZO = 9;

void beep(int n, int duration)
{
  if(n < 1)
    return;

  for (int i = 0; i < n; ++i) {
    analogWrite(PIN_PIEZO, 20);
    delay(duration);
    analogWrite(PIN_PIEZO, 0);
    delay(duration);
  }
}

void setup() {
  pinMode(PIN_PIEZO, OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  if (mySwitch.available()) {

    unsigned long value = mySwitch.getReceivedValue();

    if (value == 112233)  {
      beep(3, 100);
    }
    else if (value == 445566) {
      beep(3, 30);
    }

    mySwitch.resetAvailable();
  }
}
