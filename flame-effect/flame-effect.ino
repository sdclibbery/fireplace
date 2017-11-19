#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "rgb.h"
#include "flamecolour.h"
#include "flicker.h"
#include "fixedpoint.h"

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu
#define PIN            5

#define NUMPIXELS      1 // 30
static Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

static const char* ssid = "?";
static const char* password = "?";
static const char* mDnsHostname = "fireplace";
static ESP8266WebServer server(80);

static unsigned long frameIntervalMs = 10;
static unsigned char brightness = 255;
static unsigned int flickerSpeed = 20;
static unsigned long timeMsOffsets[NUMPIXELS];

/*
ToDo:
wifi manager
web app
OTA updates?
*/


void setup() {
  Serial.begin(115200);
  Serial.println("Start up...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500); }
  Serial.println("WiFi started");
  Serial.println(WiFi.localIP());
  MDNS.addService("http", "tcp", 80);
  MDNS.begin(mDnsHostname, WiFi.localIP());
  Serial.println("mDNS started");
  server.on("/", [](){
    server.send(200, "text/plain", "Hello World from fireplace!");
  });
  server.onNotFound([](){
    server.send(404, "text/plain", "404 not found");
  });
  server.begin();
  Serial.println("Server started");
  for(int i=0;i<NUMPIXELS;i++){
    timeMsOffsets[i] = random(100000);
  }  
  pixels.begin();
}

void loop() {
  unsigned long timeMs = millis();
  for(int i=0;i<NUMPIXELS;i++){
    unsigned long pixelTimeMs = timeMs + timeMsOffsets[i];
    unsigned char intensity = flicker(flickerSpeed, pixelTimeMs);
    Rgb rgb = rgbScale(woodFlame(intensity), brightness);
//    pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));
    pixels.setPixelColor(i, pixels.Color(128,0,90));
  }
  pixels.show();
  server.handleClient();
  delay(frameIntervalMs);
}
