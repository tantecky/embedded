#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <bsec.h>

#include "main.hpp"
#include "secret.hpp"
#include "SensorReceiver.h"

/* in minutes */
#define REPORT_INTERVAL (30)
#define MAX_RETRIES (3)

Bsec bme;

float tempOut;
byte humOut;
float tempIn;
float humIn;
float presIn;

void wait(const unsigned long minutes)
{
  const unsigned long timestamp = millis();
  const unsigned long toWait = 60 * minutes * 1000;

  do
  {
    yield();
  } while ((millis() - timestamp) < toWait);
}

void blink()
{
  digitalWrite(LED_BUILTIN, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(50); // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);
}

void initVars()
{
  tempOut = NAN;
  humOut = 0xFF;
  tempIn = NAN;
  humIn = NAN;
  presIn = NAN;
}

void read433(byte *data)
{
  // is data a ThermoHygro-device?
  if ((data[3] & 0x1f) == 0x1e)
  {
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

void enable433()
{
  SensorReceiver::init(digitalPinToInterrupt(14), read433);
}

void disable433()
{
  detachInterrupt(digitalPinToInterrupt(14));
}

void readBme()
{
}

void setup()
{
  initVars();
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);
  Wire.begin();

  bme.begin(0x77, Wire);
  checkBmeStatus();

  bsec_virtual_sensor_t sensorList[10] = {
      BSEC_OUTPUT_RAW_TEMPERATURE,
      BSEC_OUTPUT_RAW_PRESSURE,
      BSEC_OUTPUT_RAW_HUMIDITY,
      BSEC_OUTPUT_RAW_GAS,
      BSEC_OUTPUT_IAQ,
      BSEC_OUTPUT_STATIC_IAQ,
      BSEC_OUTPUT_CO2_EQUIVALENT,
      BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
      BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
  };

  bme.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
  checkBmeStatus();
}

void loop()
{
  disable433();

  readBme();

  IPAddress ip(192, 168, 168, 4);
  IPAddress gw(192, 168, 168, 1);
  IPAddress subnet(255, 255, 255, 224);

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gw, subnet);
  WiFi.begin(MYSSID, MYPASS);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  String data = "viva";

  if (!isnan(tempIn))
  {
    data += " tIn=";
    data += tempIn;
    data += ",pIn=";
    data += presIn;

    if (humIn > 0)
    {
      data += ",humIn=";
      data += humIn;
    }
  }

  if (!isnan(tempOut))
  {
    if (data.length() > 6)
    {
      data += ",";
    }
    else
    {
      data += " ";
    }

    data += "tOut=";
    data += tempOut;
    data += ",humOut=";
    data += humOut;
  }

  Serial.println(data);

  if (data.length() > 6)
  {
    for (int i = 0; i < MAX_RETRIES; i++)
    {
      HTTPClient http; //Declare object of class HTTPClient
      String url = "http://37.205.8.10:50517/write?db=mydb&u=esp&p=";
      url += DB_PASS;
      http.begin(url);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpCode = http.POST(data);    //Send the request
      String payload = http.getString(); //Get the response payload
      http.end();                        //Close connection

      Serial.println(httpCode); //Print HTTP return code
      Serial.println(payload);  //Print request response payload

      if (httpCode == HTTP_CODE_NO_CONTENT)
      {
        blink();
        break;
      }
      else
      {
        Serial.println("Unable to send data, retrying in 5s...");
        delay(5000);
      }
    }
  }

  initVars();
  WiFi.disconnect();
  Serial.print("Disconnecting");
  do
  {
    delay(500);
    Serial.print(".");
  } while (WiFi.status() == WL_CONNECTED);

  enable433();

  wait(REPORT_INTERVAL);
}

// Helper function definitions
void checkBmeStatus()
{
  String output;
  if (bme.status != BSEC_OK)
  {
    if (bme.status < BSEC_OK)
    {
      output = "BSEC error code : " + String(bme.status);
      Serial.println(output);
      for (;;)
        blink(); /* Halt in case of failure */
    }
    else
    {
      output = "BSEC warning code : " + String(bme.status);
      Serial.println(output);
    }
  }

  if (bme.bme680Status != BME680_OK)
  {
    if (bme.bme680Status < BME680_OK)
    {
      output = "BME680 error code : " + String(bme.bme680Status);
      Serial.println(output);
      for (;;)
        blink(); /* Halt in case of failure */
    }
    else
    {
      output = "BME680 warning code : " + String(bme.bme680Status);
      Serial.println(output);
    }
  }
}
