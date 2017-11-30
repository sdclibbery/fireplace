#include <Adafruit_NeoPixel.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <DNSServer.h>

#include "fireplace.h"
#include "webcontroller.h"

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu
#define PIN            5
#define NUMPIXELS      30
static Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

static const char* mDnsHostname = "fireplace";

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  WiFiManager wifiManager;
  while (!wifiManager.autoConnect("FIREPLACE-SETUP")) {
    Serial.println("WiFi start up failed.");
    delay(1000);
  }
  Serial.println("WiFi Manager done...");
  Serial.println(WiFi.localIP());

  MDNS.addService("http", "tcp", 80);
  MDNS.begin(mDnsHostname, WiFi.localIP());
  Serial.println("mDNS started");

  webControllerSetup();
  fireplaceSetup(NUMPIXELS);

  pixels.begin();
}

void loop() {
  fireplaceLoop(millis(), NUMPIXELS, [] (int i, Rgb rgb) {
    pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));
  });
  pixels.show();
  webControllerLoop();
}
