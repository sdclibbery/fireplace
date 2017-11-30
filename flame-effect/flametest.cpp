#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "rgb.h"
#include "flamecolour.h"
#include "fireplace.h"

void fp8Assert (unsigned char expected, unsigned char actual) {
  if (expected != actual) {
    printf("Expected %d but actual %d\n", expected, actual);
  }
}

void unittest (void) {
  fp8Assert(0, fp8Mul(0, 255));
  fp8Assert(0, fp8Mul(255, 0));
  fp8Assert(255, fp8Mul(255, 255));
  fp8Assert(128, fp8Mul(128, 255));
  fp8Assert(128, fp8Mul(255, 128));

  fp8Assert(255, fp8Cos(0));
  fp8Assert(124, fp8Cos(64));
  fp8Assert(0, fp8Cos(128));
  fp8Assert(131, fp8Cos(192));
  fp8Assert(255, fp8Cos(255));
}

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
  unittest();
  Rgb black = {0,0,0};
  printColouredBlock(black);
  unsigned long timeMs = 0;
  unsigned int frameIntervalMs = 10;
  unsigned int numPixels = 1;
  fireplaceSetup(numPixels);
  int c = '0';
  while (c != 'q') {
    if (c == '0') { fireplaceSetFlameFunction(woodFlame); }
    if (c == '1') { fireplaceSetFlameFunction(embersFlame); }
    if (c == '2') { fireplaceSetFlameFunction(gasFlame); }
    if (c == '3') { fireplaceSetFlameFunction(halloweenFlame); }
    if (c == '4') { fireplaceSetFlameFunction(crystalFlame); }
    if (c == '5') { fireplaceSetFlameFunction(rainbowFlame); }
    for (int n=0;n<200;n++) {
      fireplaceLoop(timeMs, numPixels, [] (int i, Rgb rgb) {
        setColour(rgb);
      });
      usleep(frameIntervalMs*1000);
      timeMs += frameIntervalMs;
    }
    printf("Enter number or q\n", c);
    fflush(stdout);
    fflush(stdin);
    c = getc(stdin);
  }
  return 0;
}
