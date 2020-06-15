#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "secret.hpp"
#include "html.hpp"

const int PIN_RELAY = 4;
bool isRelayOn = false;
ESP8266WebServer server(80);

void blink(int n = 1)
{
  for (size_t i = 0; i < n; i++)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}

void pulse()
{
  digitalWrite(PIN_RELAY, !isRelayOn);
  delay(250);
  digitalWrite(PIN_RELAY, isRelayOn);
}

void connectWifi()
{
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
  blink(3);
}

void setupPins()
{
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
}

void redirectToRoot()
{
  server.sendHeader("Location", String("/"), true);
  server.send(302, "text/plain", "");
}

void handleRoot()
{
  server.send(200, "text/html", render(isRelayOn));
}

void handlePulse()
{
  pulse();
  redirectToRoot();
}

void handleNotFound()
{
  server.send(404, "text/plain", "404: Not found bro/sis");
}

void handleOn()
{
  digitalWrite(PIN_RELAY, HIGH);
  isRelayOn = true;
  redirectToRoot();
}

void handleOff()
{
  digitalWrite(PIN_RELAY, LOW);
  isRelayOn = false;
  redirectToRoot();
}

void setupRoutes()
{
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.on("/pulse", HTTP_POST, handlePulse);
  server.on("/on", HTTP_POST, handleOn);
  server.on("/off", HTTP_POST, handleOff);
}

void setup()
{
  Serial.begin(9600);
  setupPins();
  setupRoutes();

  connectWifi();
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
