#include <math.h>
#include "fixedpoint.h"
#include "rgb.h"

static Rgb cool = { 255, 0, 0 };
static Rgb hot = { 240, 112, 4 };

Rgb flamecolour (unsigned char intensity) {
  return rgbLerp(cool, hot, intensity);
}
