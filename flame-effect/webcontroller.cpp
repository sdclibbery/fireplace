#include <ESP8266WebServer.h>
#include "fireplace.h"
#include "flamecolour.h"

static ESP8266WebServer server(80);

static void activateColourIfInArgs (String argValue, FlameFunction func) {
  if (server.arg("colour") == argValue) { fireplaceSetFlameFunction(func); }
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
  activateColourIfInArgs("purpleBlingFlame", &purpleBlingFlame);
  content += renderColourMarkup("purpleBlingFlame", "Purple Bling");

  content += "<h3>Brightness</h3>";
  Serial.println(String("Brightness: ")+server.arg("brightness"));
  if (server.hasArg("brightness")) { fireplaceSetBrightness(server.arg("brightness").toInt()); }
  content += "<p><a href=\"/?brightness=0\">Off</a>";
  content += "<a href=\"/?brightness=80\">Dim</a>";
  content += "<a href=\"/?brightness=255\">Bright</a></p>";

  content += "<h3>Flicker Speed</h3>";
  Serial.println(String("Flicker Speed: ")+server.arg("flickerSpeed"));
  if (server.hasArg("flickerSpeed")) { fireplaceSetFlickerSpeed(server.arg("flickerSpeed").toInt()); }
  content += "<p><a href=\"/?flickerSpeed=7\">Slow</a>";
  content += "<a href=\"/?flickerSpeed=9\">Normal</a>";
  content += "<a href=\"/?flickerSpeed=12\">Fast</a></p>";

  server.send(200, "text/html", content);
};

void webControllerSetup (void) {
  server.on("/", respondWithControlPage);
  server.onNotFound([]() { server.send(404, "text/plain", "404 not found"); });
  server.begin();
  Serial.println("Server started");
}

void webControllerLoop (void) {
  server.handleClient();
}
