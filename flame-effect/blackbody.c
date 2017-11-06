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
  /*
  Temperature = Kelvin / 100
  If Temperature <= 66 Then
      Green = Temperature
      Green = 99.4708025861 * Ln(Green) - 161.1195681661
      If Green < 0 Then Green = 0
      If Green > 255 Then Green = 255
  Else
      Green = Temperature - 60
      Green = 288.1221695283 * (Green ^ -0.0755148492)
      If Green < 0 Then Green = 0
      If Green > 255 Then Green = 255
  End If
  */
  return 0;
}

static unsigned char blue (unsigned int kelvin) {
  /*
  Temperature = Kelvin / 100
  If Temperature >= 66 Then
      Blue = 255
  Else

      If Temperature <= 19 Then
          Blue = 0
      Else
          Blue = Temperature - 10
          Blue = 138.5177312231 * Ln(Blue) - 305.0447927307
          If Blue < 0 Then Blue = 0
          If Blue > 255 Then Blue = 255
      End If

  End If
  */
  return 0;
}

Rgb blackbody (unsigned int kelvin) {
  Rgb rgb = { red(kelvin), green(kelvin), blue(kelvin) };
  return rgb;
}
