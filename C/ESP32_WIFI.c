#include <WiFi.h>
#include <WiFiServer.h>
#define WIFI WiFi
const char* ID = "WIFI_ID";
const char* PASSWORD = "WIFI_PASSWORD";
unsigned char recv_buffer[1024];

WiFiServer server(8000);

void setup() {
  Serial.begin(9600);

  Serial.println("WiFi:");
  Serial.println(ID);

  WiFi.begin(ID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("connecting...");
  }
  Serial.println(WIFI.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client discovered.");
    while (client.connected()) {
      if (client.available()) {
        int len = client.read(recv_buffer, 1024);
        if (len > 0) {
          recv_buffer[len] = '\0';
          Serial.print("client sent: ");
          Serial.println((char*)recv_buffer);
        } else {
        }
      }
    }
  }
}
