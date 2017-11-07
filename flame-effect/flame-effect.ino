#include <Adafruit_NeoPixel.h>

#include "rgb.h"
#include "blackbody.h"
#include "flicker.h"

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu, and connect ws2812 VIn to 3v...
#define PIN            5

// How many NeoPixels are attached?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned int timeMs = 0;
unsigned int frameIntervalMs = 10;
float brightness = 0.5f;

void setup() {
  pixels.begin();
}

void loop() {
  for(int i=0;i<NUMPIXELS;i++){
    float flicker = slowFlicker(timeMs);
    float kelvin = 300 + flicker*1200;
    float intensity = powf(flicker, 1.3f)*brightness;
    Rgb rgb = scaleRgb(blackbody(kelvin), intensity);
    pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));
  }
  pixels.show();
  delay(frameIntervalMs);
  timeMs += frameIntervalMs;
}
