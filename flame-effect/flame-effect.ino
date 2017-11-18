#include <Adafruit_NeoPixel.h>

#include "rgb.h"
#include "flamecolour.h"
#include "flicker.h"
#include "fixedpoint.h"

// Pin 5: GPIO 5: use D1 pin on lolin nodemcu
#define PIN            5

// How many NeoPixels are attached?
#define NUMPIXELS      30

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long frameIntervalMs = 10;
unsigned char brightness = 255;
unsigned long timeMsOffsets[NUMPIXELS];
unsigned int flickerSpeed = 20;

/*
ToDo:
OTA updates?
more flamecolour presets
wifi web app
*/


void setup() {
  for(int i=0;i<NUMPIXELS;i++){
    timeMsOffsets[i] = random(100000);
  }  
  pixels.begin();
}

void loop() {
  for(int i=0;i<NUMPIXELS;i++){
    unsigned long pixelTimeMs = millis() + timeMsOffsets[i];
    unsigned char intensity = fp8Mul(flicker(flickerSpeed, pixelTimeMs), brightness);
    Rgb rgb = rgbScale(gasFlame(intensity), intensity);
    pixels.setPixelColor(i, pixels.Color(rgb.r, rgb.g, rgb.b));
  }
  pixels.show();
  delay(frameIntervalMs);
}
