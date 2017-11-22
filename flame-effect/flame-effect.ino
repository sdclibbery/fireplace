#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <DNSServer.h>

#include "fireplace.h"

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

  fireplaceSetup();
}

void loop() {
  fireplaceLoop();
}
