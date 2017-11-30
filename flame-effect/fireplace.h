#include <functional>
#include "flamecolour.h"

void fireplaceSetup (unsigned int numPixels);

typedef std::function<void(int, Rgb)> SetColourFunction;
void fireplaceLoop (unsigned long timeMs, unsigned int numPixels, SetColourFunction setColour);

void fireplaceSetFlameFunction (FlameFunction flameFunction);
void fireplaceSetBrightness (unsigned char brightness);
void fireplaceSetFlickerSpeed (unsigned int flickerSpeed);
