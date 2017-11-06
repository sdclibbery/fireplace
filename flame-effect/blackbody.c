#include <math.h>

#include "rgb.h"

// blackbody radiation colours from http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/

static unsigned char red (unsigned int kelvin) {
  float temperature = kelvin / 100.0f;
  if (temperature <= 66.0f) {
      return 255;
  } else {
      float r = temperature - 60.0f;
      r = 329.698727446f * powf(r, -0.1332047592f);
      if (r < 0.0f) return 0;
      if (r > 255.0f) return 255;
      return (unsigned char) r;
  }
}

static unsigned char green (unsigned int kelvin) {
  float temperature = kelvin / 100.0f;
  if (temperature <= 66.0f) {
      float g = temperature;
      g = 99.4708025861f * logf(g) - 161.1195681661f;
      if (g < 0) return 0;
      if (g > 255) return 255;
      return g;
  } else {
      float g = temperature - 60.0f;
      g = 288.1221695283f * powf(g, -0.0755148492f);
      if (g < 0) return 0;
      if (g > 255) return 255;
      return g;
  }
}

static unsigned char blue (unsigned int kelvin) {
  float temperature = kelvin / 100.0f;
  if (temperature >= 66.0f) {
      return 255;
  } else {
      if (temperature <= 19.0f) {
          return 0;
      } else {
          float b = temperature - 10.0f;
          b = 138.5177312231f * logf(b) - 305.0447927307f;
          if (b < 0) b = 0;
          if (b > 255) b = 255;
          return b;
      }
  }
}

Rgb blackbody (unsigned int kelvin) {
  Rgb rgb = { red(kelvin), green(kelvin), blue(kelvin) };
  return rgb;
}
