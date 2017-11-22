#include <Adafruit_NeoPixel.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <DNSServer.h>

#include "rgb.h"
#include "flamecolour.h"
#include "flicker.h"
#include "fixedpoint.h"

/*
ToDo:
New speeds: 6, 9, 13; default to 9
Crystal colour: whiteish with floating hints of blue/green, and then flashes of pure white
Factor out fireplace code
 With arrays of option info plus get,set
Factor out webapp controls
manual controller
Locality effects
 One Flicker should affect several proximal LEDs
 Rainbow should smoothly move over the LED array
*/

static const char* mDnsHostname = "fireplace";
static ESP8266WebServer server(80);

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu
#define PIN            5
#define NUMPIXELS      30
static Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

typedef Rgb (*FlameFunction)(unsigned char);
static FlameFunction flameColour = &woodFlame;
static unsigned char brightness = 255;
static unsigned int flickerSpeed = 5;
static unsigned long timeMsOffsets[NUMPIXELS];

static void activateColourIfInArgs (String argValue, FlameFunction func) {
  if (server.arg("colour") == argValue) { flameColour = func; }
}
static String renderColourMarkup (String argValue, String label) {
  return String() + "<p><a href=\"/?colour=" + argValue + "\">" + label + "</a></p>";
}
static auto respondWithControlPage = [](){
  String content = "";
  content += "<style>";
  content += "body{font-family:helvetica,sans-serif;}";
  content += "a{margin:8px;padding:4px;border:1px solid #aaa;background-color:#eee;color:#111;border-radius:4px;text-decoration:none;} a:hover{background-color:#ddd;}";
  content += "</style>";
  content += "<h1>Fireplace Control</h1>";

  content += "<h3>Colours</h3>";
  Serial.println(String("Colour: ")+server.arg("colour"));
  activateColourIfInArgs("woodFlame", &woodFlame);
  content += renderColourMarkup("woodFlame", "Wood Flame");
  activateColourIfInArgs("gasFlame", &gasFlame);
  content += renderColourMarkup("gasFlame", "Gas Flame");
  activateColourIfInArgs("halloweenFlame", &halloweenFlame);
  content += renderColourMarkup("halloweenFlame", "Halloween");
  activateColourIfInArgs("rainbowFlame", &rainbowFlame);
  content += renderColourMarkup("rainbowFlame", "Rainbow");

  content += "<h3>Brightness</h3>";
  Serial.println(String("Brightness: ")+server.arg("brightness"));
  if (server.hasArg("brightness")) { brightness = server.arg("brightness").toInt(); }
  content += "<p><a href=\"/?brightness=0\">Off</a>";
  content += "<a href=\"/?brightness=80\">Dim</a>";
  content += "<a href=\"/?brightness=255\">Bright</a></p>";

  content += "<h3>Flicker Speed</h3>";
  Serial.println(String("Flicker Speed: ")+server.arg("flickerSpeed"));
  if (server.hasArg("flickerSpeed")) { flickerSpeed = server.arg("flickerSpeed").toInt(); }
  content += "<p><a href=\"/?flickerSpeed=5\">Slow</a>";
  content += "<a href=\"/?flickerSpeed=8\">Normal</a>";
  content += "<a href=\"/?flickerSpeed=13\">Fast</a></p>";

  server.send(200, "text/html", content);
};

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

  server.on("/", respondWithControlPage);
  server.onNotFound([]() { server.send(404, "text/plain", "404 not found"); });
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
    pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));
  }
  pixels.show();
  server.handleClient();
}
