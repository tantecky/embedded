#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>         
int LED = 7;
int PIR = 8;
int PIEZO = 6;

IPAddress ip(192, 168, 168, 20);
IPAddress remote(192, 168, 168, 2);
char payload[] = "ALARM!!!\n";

byte mac[] = {
  0xC3, 0x9F, 0xB4, 0x97, 0x0F, 0x2B
};

EthernetUDP client;


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(PIR, INPUT);

  Ethernet.begin(mac, ip); 
  client.begin(1337);

  delay(30000);
  beep(1, 1000);
}


void loop() {
  int state = digitalRead(PIR);
  if (state == HIGH) {
    trigger();
    delay(10000);
  }
  delay(100);
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

void beep(int n, int duration)
{
  for(int i = 0; i < n; i++)
  {
    analogWrite(PIEZO, 20);      // Almost any value can be used except 0 and 255
    // experiment to get the best tone
    delay(duration);          // wait for a duration ms
    analogWrite(PIEZO, 0);       // 0 turns it off
    delay(duration);          // wait for a duration ms   
  } 
} 

void trigger()
{
  client.beginPacket(remote, 4444);
  client.write(payload, sizeof(payload));
  client.endPacket();

  blink(5, 50);

  beep(5, 50);
}
