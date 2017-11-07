#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "rgb.h"
#include "blackbody.h"

/*
ToDo
expect 1000-1500K for the flame
*/

static void backspaceBlock () {
  printf("\033[F");
}

static void printColouredBlock (Rgb rgb) {
  printf("\x1b[38;2;%d;%d;%dm\u2588\u2588\u2588\u2588\n\u2588\u2588\u2588\u2588\x1b[0m", rgb.r, rgb.g, rgb.b);
}

static void setColour (Rgb rgb) {
  backspaceBlock();
  printColouredBlock(rgb);
  fflush(stdout);
}

static float slowFlicker (unsigned int time) {
  return 0.6f
    + 0.1f*sinf(time/31.0f)
    + 0.1f*sinf(time/53.0f)
    + 0.1f*sinf(time/753.0f)
    + 0.1f*sinf(time/1717.0f);
}

static float midFlicker (unsigned int time) {
  return 0.6f
    + 0.1f*sinf(time/19.0f)
    + 0.1f*sinf(time/31.0f)
    + 0.1f*sinf(time/73.0f)
    + 0.05f*sinf(time/753.0f)
    + 0.05f*sinf(time/1717.0f);
}

static float fastFlicker (unsigned int time) {
  return 0.6f
    + 0.1f*sinf(time/11.0f)
    + 0.1f*sinf(time/17.0f)
    + 0.1f*sinf(time/31.0f)
    + 0.05f*sinf(time/753.0f)
    + 0.05f*sinf(time/1717.0f);
}

int main () {
  Rgb black = {0,0,0};
  printColouredBlock(black);
  unsigned int time = 0;
  unsigned int frameIntervalMs = 10;
  while (1) { // Use Ctrl-C to exit :-)
    float flicker = midFlicker(time);
    float kelvin = 500 + flicker*1500;
    float intensity = flicker;
    setColour(scaleRgb(blackbody(kelvin), intensity));
    usleep(frameIntervalMs*1000);
    time += frameIntervalMs;
  }
  return 0;
}
