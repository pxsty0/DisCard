#include <WiFi.h>
#include "DisCard.h"

#define WIFI_SSID "wifi_ssid"
#define WIFI_PASS "wifi_pass"

#define WEBHOOK_URL "https://discord.com/api/webhooks/##################/###############"

DisCard discord;

void setup()
{
    Serial.begin(115200);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.print("Connecting to WiFi ...");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(" connected!");

    discord.begin(WEBHOOK_URL);

    if (discord.send("Raw message"))
    {
        Serial.println("Message sent successfully!");
    }
    else
    {
        Serial.println("Failed to send message.");
    }

    if (discord.sendEmbed("Embed Title", "This is an embedded description", "65280"))
    {
        Serial.println("Embed message sent successfully!");
    }
    else
    {
        Serial.println("Failed to send embed message.");
    }
}

void loop()
{
}
