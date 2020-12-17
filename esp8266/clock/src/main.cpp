#include "main.hpp"
#include "config.hpp"
#include "clock.hpp"
#include "sensor.hpp"

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <TaskScheduler.h>

Scheduler runner;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Oled(U8G2_R0);
WiFiUDP Udp;

Sensor sensor;

Task taskClock(100, TASK_FOREVER, Clock::tick, &runner, true);
Task taskSensor(
    20000, TASK_FOREVER, [&]() {
      sensor.tick();
    },
    &runner, true);

// #define LCDWidth                        u8g2.getDisplayWidth()
// #define ALIGN_CENTER(t)                 ((LCDWidth - (u8g2.getUTF8Width(t))) / 2)
// #define ALIGN_RIGHT(t)                  (LCDWidth -  u8g2.getUTF8Width(t))
// #define ALIGN_LEFT                      0

const uint centerOffset(const String &text)
{
  static const u8g2_uint_t width = Oled.getDisplayWidth();
  return ((width - (Oled.getUTF8Width(text.c_str()))) / 2);
}

void connect()
{
  if (isConnected())
  {
    return;
  }

  Udp.stop();
  disconnect();

  wifi_fpm_do_wakeup();
  wifi_fpm_close();

  wifi_set_opmode(STATION_MODE);
  wifi_station_connect();

  WiFi.begin(SSID, PASS);
  Serial.println("WiFi.begin");

  for (size_t i = 0; i < 10; i++)
  {
    delay(500);
    Serial.print(".");

    if (isConnected())
    {
      Serial.println();
      Serial.println("connected");

      // 8888 listen port
      Udp.begin(8888);
      break;
    }
  }
}

void disconnect()
{
  wifi_station_disconnect();
  wifi_set_opmode(NULL_MODE);
  wifi_set_sleep_type(MODEM_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
}

void setup()
{
  Serial.begin(112500);
  disconnect();

  Wire.begin(D2, D1);
  Oled.begin();
  sensor.setup();

  connect();

  Clock::setup();
}

void loop()
{
  runner.execute();
}