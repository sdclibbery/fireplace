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
    up(sqr(intensity), 32, 130),
    constant(0),
  };
  return rgbScale(rgb, intensity);
}

Rgb gasFlame (unsigned char intensity) {
  Rgb rgb = {
    up(invSqr(intensity), 0, 255),
    up(sqr(intensity), 0, 160),
    down(invSqr(intensity), 255, 0),
  };
  return rgbScale(rgb, intensity);
}

Rgb halloweenFlame (unsigned char intensity) {
  Rgb rgb = {
    constant(0),
    up(invSqr(intensity), 0, 200),
    down(invSqr(intensity), 255, 0),
  };
  return rgbScale(rgb, intensity);
}

Rgb rainbowFlame (unsigned char intensity) {
  Rgb rgb = {
    fp8Cos(intensity*2+85),
    fp8Cos(intensity*2),
    fp8Cos(intensity*2+170),
  };
  return rgb;
}
