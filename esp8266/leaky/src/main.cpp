#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <TaskScheduler.h>

// copy config.hpp.example to config.hpp and modify as you wish
#include "config.hpp"

Scheduler runner;

void blink();
void beep();
bool isConnected();
String macToStr(const uint8_t *);
void beginMqtt();
void finishMqtt();
void wifiOn();
void wifiOff();

Task taskBeep(BEEP_EACH_X_SECOND * 1000, TASK_FOREVER, beep, &runner, true);
Task taskBeginMqtt(MSG_EACH_X_MIN * 60 * 1000, TASK_FOREVER, beginMqtt, &runner, true);
Task taskFinishMqtt(500, TASK_FOREVER, finishMqtt, &runner, false);

constexpr int FPM_SLEEP_MAX_TIME = 0xFFFFFFF;

constexpr uint8_t LED_PIN = 2;
constexpr uint8_t BUZZER_PIN = 5;

void blink()
{
  digitalWrite(LED_PIN, LOW);
  delay(50);
  digitalWrite(LED_PIN, HIGH);
}

void beep()
{
  tone(BUZZER_PIN, 3000, 100);
}

inline bool isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

String macToStr(const uint8_t *mac)
{
  String result;
  for (int i = 0; i < 6; ++i)
  {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

void wifiOn()
{
  if (isConnected())
  {
    return;
  }

  wifi_fpm_do_wakeup();
  wifi_fpm_close();

  wifi_set_opmode(STATION_MODE);
  wifi_station_connect();

  WiFi.begin(SSID, PASS);
}

void wifiOff()
{
  wifi_station_disconnect();
  wifi_set_opmode(NULL_MODE);
  wifi_set_sleep_type(MODEM_SLEEP_T);
  wifi_fpm_open();
  wifi_fpm_do_sleep(FPM_SLEEP_MAX_TIME);
}

void finishMqtt()
{
  if (!isConnected())
  {
    return;
  }

  WiFiClient wifiClient;
  PubSubClient client(MQTT, PORT, wifiClient);

  String clientName = "Leaky-";
  uint8_t mac[6];

  WiFi.macAddress(mac);
  clientName += macToStr(mac);

  if (client.connect(clientName.c_str()))
  {
    const unsigned long secs = millis() / 1000;
    String msg(TOPIC);
    msg += "\nuptime (s): " + String(secs, 10);

    if (client.publish(TOPIC, msg.c_str(), msg.length()))
    {
      blink();
      client.disconnect();
      wifiOff();
      taskFinishMqtt.disable();
    }
    else
    {
      client.disconnect();
    }
  }
}

void beginMqtt()
{
  wifiOn();
  taskFinishMqtt.enable();
}

void setup()
{
  wifiOff();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(BUZZER_PIN, OUTPUT);

  runner.startNow();
  taskBeep.forceNextIteration();
  taskBeginMqtt.forceNextIteration();
}

void loop()
{
  runner.execute();
}