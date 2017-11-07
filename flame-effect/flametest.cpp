#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "rgb.h"
#include "blackbody.h"
#include "flicker.h"

/*
ToDo
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

int main () {
  Rgb black = {0,0,0};
  printColouredBlock(black);
  unsigned int timeMs = 0;
  unsigned int frameIntervalMs = 10;
  while (1) { // Use Ctrl-C to exit :-)
    float flicker = midFlicker(timeMs);
    float kelvin = 500 + flicker*2000;
    float intensity = flicker;
    setColour(scaleRgb(blackbody(kelvin), intensity));
    usleep(frameIntervalMs*1000);
    timeMs += frameIntervalMs;
  }
  return 0;
}
