#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "DESKTOP-9L28D8O 0542";
const char* password = "12345678";

#define LED_PIN 2   // Change based on your board's LED pin

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("\n--- ESP32 WiFi LED Status Logic ---");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  delay(300);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
}

void loop() {

  wl_status_t wifiStatus = WiFi.status();

  // ------------------------------------------
  // 1️⃣ WiFi NOT FOUND / FAILED → LED OFF
  // ------------------------------------------
  if (wifiStatus == WL_NO_SSID_AVAIL || 
      wifiStatus == WL_CONNECT_FAILED ||
      wifiStatus == WL_IDLE_STATUS) 
  {
    digitalWrite(LED_PIN, LOW);  // LED OFF
    Serial.print(" X ");         // SSID not found or failed
    delay(500);
    return;
  }

  // ------------------------------------------
  // 2️⃣ WiFi CONNECTING → BLINK LED
  // ------------------------------------------
  if (wifiStatus != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
    return;
  }

  // ------------------------------------------
  // 3️⃣ WiFi CONNECTED → LED HIGH (Solid ON)
  // ------------------------------------------
  static bool printed = false;

  if (!printed) {
    printed = true;
    Serial.println("\n✓ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_PIN, HIGH);  // Turn LED solid ON
  }

  delay(1000);
}
