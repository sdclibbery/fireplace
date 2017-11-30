#include <stdlib.h>

#include "fireplace.h"
#include "flamecolour.h"

/*
ToDo:
Factor out webapp controls
manual controller
*/

static FlameFunction flameColour = &woodFlame;
static unsigned char brightness = 255;
static unsigned int flickerSpeed = 7;

void fireplaceSetFlameFunction (FlameFunction newFlameFunction) {
  flameColour = newFlameFunction;
}

void fireplaceSetBrightness (unsigned char newBrightness) {
  brightness = newBrightness;
}

void fireplaceSetFlickerSpeed (unsigned int newFlickerSpeed) {
  flickerSpeed = newFlickerSpeed;
}

void fireplaceSetup (unsigned int) {
}

void fireplaceLoop (unsigned long timeMs, unsigned int numPixels, SetColourFunction setColour) {
  for(int i=0;i<numPixels;i++){
    unsigned char fractionalPosition = i*255/numPixels;
    Rgb rgbFlame = flameColour(fractionalPosition, timeMs*flickerSpeed);
    Rgb rgb = rgbScale(rgbFlame, brightness);
    setColour(i, rgb);
  }
}
