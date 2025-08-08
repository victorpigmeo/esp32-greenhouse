#include <DHT.h>
#include <WiFi.h>

#include "auth_info.h"
#include "servers/http_server.h"

// Aux pins
#define RELAY_P1 12
#define RELAY_P2 13
#define RELAY_P3 14
#define RELAY_P4 15
#define DHT_PIN 16

// HttpServer instance
WiFiServer server(8080);

// DHT Instance
DHT dht(DHT_PIN, DHT22);

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  dht.begin();

  pinMode(RELAY_P1, OUTPUT);
  pinMode(RELAY_P2, OUTPUT);
  pinMode(RELAY_P3, OUTPUT);
  pinMode(RELAY_P4, OUTPUT);

  // Connect WiFi
  Serial.print("Connecting to ");
  Serial.print(AuthInfo::wifi_ssid);
  WiFi.begin(AuthInfo::wifi_ssid, AuthInfo::wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.println();

  // Start HTTP Server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    HttpServer::handleRequest(client, stream_httpd, dht);

    client.stop();
  }
}
