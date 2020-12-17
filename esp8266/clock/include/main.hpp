#ifndef C62B6AE7_FD38_4A0F_9EB2_4A3FB116DEAB
#define C62B6AE7_FD38_4A0F_9EB2_4A3FB116DEAB
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <WiFiUdp.h>

extern U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Oled;
constexpr int FPM_SLEEP_MAX_TIME = 0xFFFFFFF;

WiFiUDP Udp;

inline bool isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void connect();
void disconnect();
const uint centerOffset(const String &text)

#endif /* C62B6AE7_FD38_4A0F_9EB2_4A3FB116DEAB */
