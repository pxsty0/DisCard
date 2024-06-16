#include "DisCard.h"

void DisCard::begin(String webhookURL)
{
  DisCard::webhookURL = webhookURL;
}

bool DisCard::send(String content)
{
  return DisCard::sendRequest("{\"content\":\"" + content + "\",\"tts\":false}");
}

bool DisCard::sendEmbed(String title, String description, String color)
{
  String embedContent = "{\"embeds\":[{\"title\":\"" + title + "\",\"description\":\"" + description + "\",\"color\":" + color + "}]}";
  return DisCard::sendRequest(embedContent);
}

bool DisCard::sendRequest(String jsonPayload)
{
  WiFiClientSecure *client = new WiFiClientSecure;
  bool ok = false;
  if (client)
  {
    client->setInsecure();

    HTTPClient https;

    if (https.begin(*client, DisCard::webhookURL))
    {
      https.addHeader("Content-Type", "application/json");

      int httpCode = https.POST(jsonPayload);
      if (httpCode > 0)
      {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_NO_CONTENT)
        {
          ok = true;
        }
        else
        {
          ok = false;
        }
        https.end();
      }
      else
      {
        ok = false;
      }
    }
    else
    {
      ok = false;
    }
  }
  else
  {
    ok = false;
  }
  delete client;
  return ok;
}
