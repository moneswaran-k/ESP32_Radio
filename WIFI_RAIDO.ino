#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_PASSWORD";

WiFiUDP udp;

const uint16_t PORT = 5005;

uint8_t buffer[512];

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(PORT);

  Serial.println("Waiting for audio...");
}

void loop() {

  int packetSize = udp.parsePacket();

  if (packetSize > 0) {

    int len = udp.read(buffer, sizeof(buffer));

    for (int i = 0; i < len; i++) {

      // Output the same sample to Left and Right
      dacWrite(25, buffer[i]);
      dacWrite(26, buffer[i]);

      // Approximate 22.05 kHz sample rate
      delayMicroseconds(45);
    }
  }
}