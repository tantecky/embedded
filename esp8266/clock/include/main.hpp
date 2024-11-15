#ifndef C62B6AE7_FD38_4A0F_9EB2_4A3FB116DEAB
#define C62B6AE7_FD38_4A0F_9EB2_4A3FB116DEAB

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <TM1637Display.h>
#include <WiFiUdp.h>

constexpr unsigned long LOG_EACH_MIN = 30 * 60 * 1000;
constexpr unsigned long FIRTS_LOG_AFTER = 5 * 60 * 1000 - LOG_EACH_MIN;

extern U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Oled;
extern TM1637Display Led;

constexpr int FPM_SLEEP_MAX_TIME = 0xFFFFFFF;

extern WiFiUDP Udp;

inline bool isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void connect();
void disconnect();
const uint centerOffset(const String &text);
void setContrast();

#endif /* C62B6AE7_FD38_4A0F_9EB2_4A3FB116DEAB */
