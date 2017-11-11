#include <math.h>
#include "rgb.h"

static Rgb cool = { 160, 8, 0 };
static Rgb hot = { 255, 160, 4 };

Rgb flamecolour (unsigned char intensity) {
  return rgbLerp(cool, hot, intensity);
}
