#include "Arduino.h"
#include "fireplace.h"
#include "flicker.h"
#include "flamecolour.h"

/*
ToDo:
Use fireplace.cpp in PC test build
 With arrays of option info plus get,set
Have smoother crystal and rainbow effects
 Pass time into flamecolour and have flamecolour call flicker
Rainbow moves along string of LEDs, instead of each LED havingits own individual rainbow effect
 Pass LED index into flamecolour
Factor out webapp controls
manual controller
*/

static FlameFunction flameColour = &woodFlame;
static unsigned char brightness = 255;
static unsigned int flickerSpeed = 7;
static unsigned long* timeMsOffsets = NULL;

void fireplaceSetFlameFunction (FlameFunction newFlameFunction) {
  flameColour = newFlameFunction;
}

void fireplaceSetBrightness (unsigned char newBrightness) {
  brightness = newBrightness;
}

void fireplaceSetFlickerSpeed (unsigned int newFlickerSpeed) {
  flickerSpeed = newFlickerSpeed;
}

void fireplaceSetup (unsigned int numPixels) {
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
}
