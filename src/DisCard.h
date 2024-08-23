#ifndef DisCard_h
#define DisCard_h

#include <Arduino.h>

#if defined(ESP32)
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#else
#error "DisCard Only Works on ESP32 Based Cards"
#endif

class DisCard
{
public:
  void begin(String webhookURL);
  bool send(String content);
  bool sendEmbed(String title, String description, String color);

private:
  bool sendRequest(String jsonPayload);

  WiFiMulti wifi;
  String webhookURL;
};

#endif
