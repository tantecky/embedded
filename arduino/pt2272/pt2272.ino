/*
  Example for different sending methods

  https://github.com/sui77/rc-switch/

*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  pinMode(8, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);



  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(10);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);

}

void loop() {

  if (digitalRead(8) == LOW)
  {
  digitalWrite(LED_BUILTIN, HIGH);
    for (size_t i = 0; i < 10; i++)
    {
      /* code */
  mySwitch.sendTriState("FFFFFFFF0000");
    }
  digitalWrite(LED_BUILTIN, LOW);

    /* code */
  }


  /* Same switch as above, but tri-state code */
  // delay(250);

}
