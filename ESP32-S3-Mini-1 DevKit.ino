#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 48       // Built-in RGB LED pin on ESP32-S3
#define NUM_PIXELS 1     // Only one RGB LED

Adafruit_NeoPixel pixel(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

const char* ssid     = "DESKTOP-9L28D8O 0542";
const char* password = "12345678";

bool wifiConnected = false;

void setup() {
  Serial.begin(115200);

  pixel.begin();
  pixel.clear();
  pixel.show();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
}

void loop() {

  // Check WiFi status
  if (WiFi.status() == WL_CONNECTED) {
    if (!wifiConnected) {
      Serial.println("\nWiFi Connected!");
      wifiConnected = true;
    }
    rgbConnectedPattern();
  } else {
    wifiConnected = false;
    solidRed();
  }
}

// --------------------------------------------------
// FUNCTION: Solid RED when not connected
// --------------------------------------------------
void solidRed() {
  pixel.setPixelColor(0, pixel.Color(255, 0, 0)); 
  pixel.show();
  delay(200);
}

// --------------------------------------------------
// FUNCTION: RGB Breathing Pattern when connected
// --------------------------------------------------
void rgbConnectedPattern() {
  static uint8_t brightness = 0;
  static int8_t step = 5;

  brightness += step;
  if (brightness == 0 || brightness == 255) step = -step;

  // RGB cycle breathing
  uint32_t color = pixel.Color(
      (sin(brightness * 0.1) + 1) * 127,
      (sin(brightness * 0.1 + 2) + 1) * 127,
      (sin(brightness * 0.1 + 4) + 1) * 127
  );

  pixel.setPixelColor(0, color);
  pixel.setBrightness(brightness);
  pixel.show();
  delay(20);
}
