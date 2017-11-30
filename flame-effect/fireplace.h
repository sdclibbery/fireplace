#include <functional>
#include "rgb.h"

void fireplaceSetup (unsigned int numPixels);

typedef std::function<void(int, Rgb)> SetColourFunction;
void fireplaceLoop (unsigned int numPixels, SetColourFunction setColour);

typedef Rgb (*FlameFunction)(unsigned char);
void fireplaceSetFlameFunction (FlameFunction flameFunction);
void fireplaceSetBrightness (unsigned char brightness);
void fireplaceSetFlickerSpeed (unsigned int flickerSpeed);
