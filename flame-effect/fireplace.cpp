#include <ESP8266WebServer.h>

#include "fireplace.h"
#include "flamecolour.h"
#include "flicker.h"
#include "fixedpoint.h"

/*
ToDo:
Use fireplace.cpp in PC test build
 Factor out fireplace code into reusable controller, NeoPixel output and WebServer controls
 With arrays of option info plus get,set
Have smoother crystal and rainbow effects
 Pass time into flamecolour and have flamecolour call flicker
Rainbow moves along string of LEDs, instead of each LED havingits own individual rainbow effect
 Pass LED index into flamecolour
Factor out webapp controls
manual controller
*/

static ESP8266WebServer server(80);

typedef Rgb (*FlameFunction)(unsigned char);
static FlameFunction flameColour = &woodFlame;
static unsigned char brightness = 255;
static unsigned int flickerSpeed = 7;
static unsigned long* timeMsOffsets = NULL;

static void activateColourIfInArgs (String argValue, FlameFunction func) {
  if (server.arg("colour") == argValue) { flameColour = func; }
}
static String renderColourMarkup (String argValue, String label) {
  return String() + "<p><a href=\"/?colour=" + argValue + "\">" + label + "</a></p>";
}
static auto respondWithControlPage = [](){
  String content = "";
  content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  content += "<style>";
  content += "body{font-family:helvetica,sans-serif;}";
  content += "a{margin:8px;padding:4px;border:1px solid #aaa;background-color:#eee;color:#111;border-radius:4px;text-decoration:none;} a:hover{background-color:#ddd;}";
  content += "</style>";
  content += "<h1>Fireplace Control</h1>";

  content += "<h3>Colours</h3>";
  Serial.println(String("Colour: ")+server.arg("colour"));
  activateColourIfInArgs("woodFlame", &woodFlame);
  content += renderColourMarkup("woodFlame", "Wood Flame");
  activateColourIfInArgs("embersFlame", &embersFlame);
  content += renderColourMarkup("embersFlame", "Glowing Embers");
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

void fireplaceSetup (unsigned int numPixels) {
  server.on("/", respondWithControlPage);
  server.onNotFound([]() { server.send(404, "text/plain", "404 not found"); });
  server.begin();
  Serial.println("Server started");

  timeMsOffsets = new unsigned long [numPixels];
  for(int i=0;i<numPixels;i++){
    timeMsOffsets[i] = random(100000);
  }
}

void fireplaceLoop (unsigned int numPixels, SetColourFunction setColour) {
  unsigned long timeMs = millis();
  for(int i=0;i<numPixels;i++){
    unsigned long pixelTimeMs = timeMs + timeMsOffsets[i];
    unsigned char intensity = flicker(flickerSpeed, pixelTimeMs);
    Rgb rgb = rgbScale(flameColour(intensity), brightness);
    setColour(i, rgb);
  }
  server.handleClient();
}
