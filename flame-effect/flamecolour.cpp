#include <math.h>
#include "fixedpoint.h"
#include "rgb.h"

static inline unsigned char constant (unsigned char v) {
  return v;
}
static inline unsigned char sqr (unsigned char x) {
  return fp8Mul(x, x);
}
static inline unsigned char invSqr (unsigned char x) {
  return 255 - fp8Mul((255-x), (255-x));
}
static inline unsigned char up (unsigned char x, unsigned char from, unsigned char to) {
  return from + fp8Mul(x, to - from);
}
static inline unsigned char down (unsigned char x, unsigned char from, unsigned char to) {
  return to + fp8Mul(255-x, from-to);
}

Rgb woodFlame (unsigned char intensity) {
  Rgb rgb = {
    constant(255),
    up(sqr(intensity), 0, 160),
    down(intensity, 48, 0),
  };
  return rgb;
}

Rgb gasFlame (unsigned char intensity) {
  Rgb rgb = {
    up(intensity, 0, 255),
    up(sqr(intensity), 0, 160),
    down(intensity, 255, 0),
  };
  return rgb;
}

Rgb halloweenFlame (unsigned char intensity) {
  Rgb rgb = {
    constant(0),
    up(intensity, 40, 255),
    down(intensity, 255, 0),
  };
  return rgb;
}
