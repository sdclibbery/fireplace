#include "rgb.h"
#include "fixedpoint.h"

Rgb scaleRgb (Rgb c, unsigned char s) {
  Rgb out = { fp8Mul(c.r, s), fp8Mul(c.g, s), fp8Mul(c.b, s) };
  return out;
}
