#include <Adafruit_NeoPixel.h>
#include <ESP8266WebServer.h>

#include "rgb.h"
#include "flamecolour.h"
#include "flicker.h"
#include "fixedpoint.h"

/*
ToDo:
manual controller
remember last settings?
Rainbow should have better colours; ie actual Hue
*/

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu
#define PIN            5
#define NUMPIXELS      30
static Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

static ESP8266WebServer server(80);

typedef Rgb (*FlameFunction)(unsigned char);
static FlameFunction flameColour = &woodFlame;
static unsigned char brightness = 255;
static unsigned int flickerSpeed = 7;
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
  activateColourIfInArgs("crystalFlame", &crystalFlame);
  content += renderColourMarkup("crystalFlame", "Crystal");
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
  content += "<p><a href=\"/?flickerSpeed=7\">Slow</a>";
  content += "<a href=\"/?flickerSpeed=9\">Normal</a>";
  content += "<a href=\"/?flickerSpeed=12\">Fast</a></p>";

  server.send(200, "text/html", content);
};

void fireplaceSetup (void) {
  server.on("/", respondWithControlPage);
  server.onNotFound([]() { server.send(404, "text/plain", "404 not found"); });
  server.begin();
  Serial.println("Server started");

  for(int i=0;i<NUMPIXELS;i++){
    timeMsOffsets[i] = random(100000);
  }
  pixels.begin();
}

void fireplaceLoop (void) {
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
