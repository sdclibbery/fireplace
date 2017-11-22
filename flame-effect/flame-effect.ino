#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <DNSServer.h>

#include "fireplace.h"

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
