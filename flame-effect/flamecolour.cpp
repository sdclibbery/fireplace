#include <math.h>
#include "fixedpoint.h"
#include "rgb.h"

Rgb flamecolour (unsigned char intensity) {
  unsigned int sqr = fp8Mul(intensity, intensity);
  Rgb rgb = {
    255,
    fp8Mul(sqr, 160),
    48 - fp8Mul(intensity, 48)
  };
  return rgb;
}
