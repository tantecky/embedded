#include "main.hpp"
#include "config.hpp"
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <TimeLib.h>
#include <ESP8266WiFi.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Oled(U8G2_R0);

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

// NTP Servers:
static const char ntpServerName[] = "cz.pool.ntp.org";

const int timeZone = 1; // Central European Time

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

void setup()
{
  Serial.begin(112500);
  disconnect();

  Wire.begin(D2, D1);
  Oled.begin();

  connect();

  setSyncProvider(getNtpTime);
  setSyncInterval(300);
}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop()
{
  if (!isConnected())
  {
    connect();
  }

  if (timeStatus() != timeNotSet)
  {
    if (now() != prevDisplay)
    { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();
    }
  }
}

void digitalClockDisplay()
{
  Oled.clearBuffer();                    // clear the internal memory
  Oled.setFont(u8g2_font_logisoso32_tr); // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall

  String text = String(hour());
  text += ":";

  const int min = minute();

  if (min < 10)
  {
    text += "0";
  }

  text += String(min);

  Oled.drawStr(centerOffset(text), 32, text.c_str()); // write something to the internal memory

  Oled.sendBuffer(); // transfer internal memory to the display
  // // digital clock display of the time
  // Serial.print(hour());
  // printDigits(minute());
  // printDigits(second());
  // Serial.print(" ");
  // Serial.print(day());
  // Serial.print(".");
  // Serial.print(month());
  // Serial.print(".");
  // Serial.print(year());
  // Serial.println();
}

// void printDigits(int digits)
// {
//   // utility for digital clock display: prints preceding colon and leading 0
//   Serial.print(":");
//   if (digits < 10)
//     Serial.print('0');
//   Serial.print(digits);
// }

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48;     // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  if (!isConnected())
  {
    return 0;
  }

  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0)
    ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500)
  {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE)
    {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE); // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 = (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0;          // Stratum, or type of clock
  packetBuffer[2] = 6;          // Polling Interval
  packetBuffer[3] = 0xEC;       // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}