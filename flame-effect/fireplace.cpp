#include <stdlib.h>

#include "fireplace.h"
#include "flamecolour.h"

/*
ToDo:
Have smoother crystal and rainbow effects
 Pass time into flamecolour and have flamecolour call flicker
Rainbow moves along string of LEDs, instead of each LED havingits own individual rainbow effect
 Pass fractional LED index into flamecolour
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
    timeMsOffsets[i] = (unsigned long)rand()*100000/RAND_MAX;
  }
}

void fireplaceLoop (unsigned long timeMs, unsigned int numPixels, SetColourFunction setColour) {
  for(int i=0;i<numPixels;i++){
    unsigned long pixelTimeMs = timeMs + timeMsOffsets[i];
    Rgb rgb = rgbScale(flameColour(pixelTimeMs*flickerSpeed), brightness);
    setColour(i, rgb);
  }
}
