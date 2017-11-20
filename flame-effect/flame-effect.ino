#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>

#include "rgb.h"
#include "flamecolour.h"
#include "flicker.h"
#include "fixedpoint.h"

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu
#define PIN            5

#define NUMPIXELS      1 // 30
static Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

static const char* mDnsHostname = "fireplace";
static ESP8266WebServer server(80);

typedef Rgb (*FlameFunction)(unsigned char);

static unsigned long frameIntervalMs = 10;
static unsigned char brightness = 255;
static FlameFunction flameColour = &woodFlame;
static unsigned int flickerSpeed = 20;
static unsigned long timeMsOffsets[NUMPIXELS];

/*
ToDo:
web app
OTA updates?
*/


void setup() {
  Serial.begin(115200);
  Serial.println("Start up...");
  
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
  
  server.on("/", [](){
    String content = "";
    content += "<style>";
    content += "body{font-family:helvetica,sans-serif;}";
    content += "a{margin:8px;padding:4px;border:1px solid #aaa;background-color:#eee;color:#111;border-radius:4px;} a:hover{background-color:#ddd;}";
    content += "</style>";
    content += "<h1>Fireplace Control</h1>";
    content += "<h3>Preset Effects</h3>";
    Serial.println(String("Preset: ")+server.arg("preset"));
    content += "<p><a href=\"/?preset=woodFlame\">Wood Flame</a></p>";
    if (server.arg("preset") == "woodFlame") { flameColour = &woodFlame; }
    content += "<p><a href=\"/?preset=gasFlame\">Gas Flame</a></p>";
    if (server.arg("preset") == "gasFlame") { flameColour = &gasFlame; }
    content += "<p><a href=\"/?preset=halloweenFlame\">Halloween</a></p>";
    if (server.arg("preset") == "halloweenFlame") { flameColour = &halloweenFlame; }
    content += "<p><a href=\"/?preset=rainbowFlame\">Gas Flame</a></p>";
    if (server.arg("preset") == "rainbowFlame") { flameColour = &rainbowFlame; }
    server.send(200, "text/html", content);
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
    Rgb rgb = rgbScale(flameColour(intensity), brightness);
//    pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));
    pixels.setPixelColor(i, pixels.Color(128,0,90));
  }
  pixels.show();
  server.handleClient();
  delay(frameIntervalMs);
}
