#include "rgb.h"

unsigned char scale (unsigned char x, float s) {
  return x*s;
}

Rgb scaleRgb (Rgb c, float s) {
  Rgb out = { scale(c.r, s), scale(c.g, s), scale(c.b, s) };
  return out;
}
