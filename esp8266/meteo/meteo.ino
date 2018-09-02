/*
 * This sketch receives and decodes data from a 433MHz thermo/hygro weather sensor.
 * The received data (temperature, humidity, channel) is echo
 *
 * Setup:
 * - Connect digital output of a 433MHz receiver to digital pin 2 of Arduino
 * - Enable the serial monitor at 115200 baud.
 *
 */

// D1 = SCL
// D2 = SDA
// D5 = RX 433 MHz

#include "secret.hpp"
#include <BME280I2C.h>
#include <math.h>
#include <Wire.h> // Needed for legacy versions of Arduino.
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SensorReceiver.h>

/* in minutes */
#define REPORT_INTERVAL (5)

Ticker flipper;
volatile bool tick = false;
float tempOut;
byte humOut;
float tempIn;
float humIn;
float presIn;

BME280I2C::Settings settings(
    BME280::OSR_X16,
    BME280::OSR_X16,
    BME280::OSR_X16,
    BME280::Mode_Normal,
    BME280::StandbyTime_500us,
    BME280::Filter_16,
    BME280::SpiEnable_False,
    BME280I2C::I2CAddr_0x76);

BME280I2C bme(settings);

void initVars()
{
  tempOut = NAN;
  humOut = 0xFF;
  tempIn = NAN;
  humIn = NAN;
  presIn = NAN;
}

void report()
{
  tick = true;
}

void blink()
{
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(50); // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);
}

void enable433()
{
  SensorReceiver::init(digitalPinToInterrupt(14), read433);
}

void disable433()
{
  detachInterrupt(digitalPinToInterrupt(14));
}

void setup()
{
  initVars();
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(9600);
  Wire.begin();

  while (!bme.begin()) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Could not find BME280I2C sensor!");
    delay(1000);
  }
  digitalWrite(LED_BUILTIN, HIGH);

  flipper.attach(60 * REPORT_INTERVAL, report);
  enable433();
}

void readBme()
{

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_Pa);

  bme.read(presIn, tempIn, humIn, tempUnit, presUnit);
}

void loop()
{
  if (tick) {
    tick = false;

    disable433();

    readBme();

    WiFi.begin(MYSSID, MYPASS);

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    String data = "viva";

    if (!isnan(tempIn)) {
      data += " tIn=";
      data += tempIn;
      data += ",pIn=";
      data += presIn;

      if (humIn > 0) {
        data += ",humIn=";
        data += humIn;
      }
    }

    if (!data.length() < 6) {
      data += ",";
    } else {
      data += " ";
    }

    if (!isnan(tempOut)) {
      data += "tOut=";
      data += tempOut;
      data += ",humOut=";
      data += humOut;
    }

    Serial.println(data);

    if (data.length() > 6) {

      HTTPClient http; //Declare object of class HTTPClient
      String url = "http://37.205.8.10:50517/write?db=mydb&u=esp&p=";
      url += DB_PASS;
      http.begin(url);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpCode = http.POST(data); //Send the request
      String payload = http.getString(); //Get the response payload
      http.end(); //Close connection

      Serial.println(httpCode); //Print HTTP return code
      Serial.println(payload); //Print request response payload

      if (httpCode == 204) {
        blink();
      }
    }
    initVars();
    WiFi.disconnect();
    enable433();
  }
}

void read433(byte* data)
{
  // is data a ThermoHygro-device?
  if ((data[3] & 0x1f) == 0x1e) {
    // Yes!

    byte channel, randomId;
    int temp;
    byte humidity;

    // Decode the data
    SensorReceiver::decodeThermoHygro(data, channel, randomId, temp, humidity);

    tempOut = (temp / 10) + ((temp % 10) / 10.);
    humOut = humidity;
  }
}
