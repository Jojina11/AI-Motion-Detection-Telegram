#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ssid";
const char* password = "password";
const char* server = "http://YOUR_LAPTOP_IP:5000/photo"; 
const char* telegramToken = "YOUR_TELEGRAM_BOT_TOKEN";
const char* chatId = "YOUR_CHAT_ID";

WiFiServer wifiServer(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  if (client) {
    String request = client.readStringUntil('\r');
    if (request.indexOf("/trigger") != -1) {
      sendPhotoToTelegram();
    }
    client.flush();
  }
}

void sendPhotoToTelegram() {
  HTTPClient http;
  WiFiClient client;

  Serial.println("Requesting image from server...");
  http.begin(client, server);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    WiFiClient* stream = http.getStreamPtr();

    Serial.println("Sending image to Telegram...");
    HTTPClient telegram;
    String url = "https://api.telegram.org/bot" + String(telegramToken) + "/sendPhoto?chat_id=" + String(chatId);
    telegram.begin(client, url);
    telegram.addHeader("Content-Type", "image/jpeg");

    int httpResponseCode = telegram.sendRequest("POST", stream, http.getSize());

    if (httpResponseCode > 0) {
      Serial.println("Photo sent successfully!");
    } else {
      Serial.println("Failed to send photo.");
    }

    telegram.end();
  } else {
    Serial.println("Failed to get photo from server.");
  }

  http.end();
}
