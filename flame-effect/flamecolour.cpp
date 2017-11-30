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
static unsigned char flicker (unsigned long time) {
  return 32
    + fp8Mul(48, fp8Cos(time/19))
    + fp8Mul(64, fp8Cos(time/31))
    + fp8Mul(48, fp8Cos(time/73))
    + fp8Mul(32, fp8Cos(time/753))
    + fp8Mul(32, fp8Cos(time/1717));
}

Rgb woodFlame (unsigned long time) {
  unsigned char intensity = flicker(time);
  Rgb rgb = {
    constant(255),
    up(sqr(intensity), 32, 120),
    constant(0),
  };
  return rgbScale(rgb, intensity);
}

Rgb embersFlame (unsigned long time) {
  unsigned char intensity = flicker(time);
  Rgb rgb = {
    constant(255),
    up(sqr(sqr(intensity)), 0, 80),
    constant(0),
  };
  return rgbScale(rgb, intensity/3);
}

Rgb gasFlame (unsigned long time) {
  unsigned char intensity = flicker(time);
  Rgb rgb = {
    up(intensity, 0, 255),
    up(sqr(intensity), 0, 160),
    down(invSqr(intensity), 255, 0),
  };
  return rgbScale(rgb, intensity);
}

Rgb halloweenFlame (unsigned long time) {
  unsigned char intensity = flicker(time);
  Rgb rgb = {
    constant(0),
    up(invSqr(intensity), 0, 200),
    down(invSqr(intensity), 255, 0),
  };
  return rgbScale(rgb, intensity);
}

Rgb crystalFlame (unsigned long time) {
  if (time%1000 == 0) {
    static Rgb white = {255, 255, 255};
    return white;
  }
  Rgb rgb = {
    constant(60),
    down(fp8Cos(time/7), 65, 50),
    up(fp8Cos(time/7), 55, 70),
  };
  return rgb;
}

Rgb rainbowFlame (unsigned long time) {
  Rgb rgb = {
    fp8Cos(time/31),
    fp8Cos(time/31+85),
    fp8Cos(time/31+170),
  };
  return rgb;
}
