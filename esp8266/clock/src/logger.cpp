#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include "main.hpp"
#include "logger.hpp"
#include "sensor.hpp"
#include "remote.hpp"
#include "config.hpp"

void Logger::setup()
{
}

void Logger::tick()
{
    if (!isConnected())
    {
        connect();
    }

    // report interval
    if (millis() - lastReport_ < LOG_EACH_MIN)
    {
        return;
    }

    String data = "vresina";

    const double tempIn = Sensor.temperature();
    const double humIn = Sensor.humidity();
    const double presIn = Sensor.pressure();

    if (!isnan(tempIn))
    {
        data += " tIn=";
        data += tempIn;
        data += ",pIn=";
        data += presIn;

        data += ",humIn=";
        data += humIn;
    }

    const float tOut = Remote::temperature;

    if (!isnan(tOut))
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
        data += tOut;
    }

    if (data.length() > 6)
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
            lastReport_ = millis();
        }
    }
}