#include <math.h>

#include "rgb.h"

// blackbody radiation colours from http://www.tannerhelland.com/4435/convert-hectokelvin-rgb-algorithm-code/

static unsigned char clamp (float x) {
    return x < 0.0f ? 0 : (x > 255.0f ? 255 : x);
}

static unsigned char red (unsigned int kelvin) {
  if (kelvin <= 6600.0f) {
      return 255;
  } else {
      float r = kelvin/100.0f - 60.0f;
      r = 329.698727446f * powf(r, -0.1332047592f);
      return clamp(r);
  }
}

static unsigned char green (unsigned int kelvin) {
  if (kelvin <= 6600.0f) {
      float g = kelvin / 100.0f;
      g = 99.4708025861f * logf(g) - 161.1195681661f;
      return clamp(g);
  } else {
      float g = kelvin/100.0f - 60.0f;
      g = 288.1221695283f * powf(g, -0.0755148492f);
      return clamp(g);
  }
}

static unsigned char blue (unsigned int kelvin) {
  if (kelvin >= 6600.0f) {
      return 255;
  } else {
      if (kelvin <= 1900.0f) {
          return 0;
      } else {
          float b = kelvin/100.0f - 10.0f;
          b = 138.5177312231f * logf(b) - 305.0447927307f;
          return clamp(b);
      }
  }
}

Rgb blackbody (unsigned int kelvin) {
  Rgb rgb = { red(kelvin), green(kelvin), blue(kelvin) };
  return rgb;
}
