#pragma once
#include "fixedpoint.h"

typedef struct Rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Rgb;

static inline Rgb rgbScale (Rgb c, unsigned char s) {
  Rgb out = { fp8Mul(c.r, s), fp8Mul(c.g, s), fp8Mul(c.b, s) };
  return out;
}

static inline Rgb rgbAdd (Rgb l, Rgb r) {
  Rgb out = { (unsigned char)(l.r+r.r), (unsigned char)(l.g+r.g), (unsigned char)(l.b+r.b) };
  return out;
}

static inline Rgb rgbLerp (Rgb lo, Rgb hi, unsigned char x) {
  return rgbAdd(rgbScale(hi, x), rgbScale(lo, 255-x));
}
