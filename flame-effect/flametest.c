#include <stdio.h>
#include <unistd.h>

#include "rgb.h"
#include "blackbody.h"

/*
ToDo
*/

static void backspaceBlock () {
  printf("\033[F");
}

static void printColouredBlock (Rgb rgb) {
  printf("\x1b[38;2;%d;%d;%dm\u2588\u2588\u2588\u2588\n\u2588\u2588\u2588\u2588\x1b[0m", rgb.r, rgb.g, rgb.b);
}

static void setColor (Rgb rgb) {
  backspaceBlock();
  printColouredBlock(rgb);
  fflush(stdout);
}

int main () {
  Rgb black = {0,0,0};
  printColouredBlock(black);
  for (unsigned char i=0; i<255; i++) {
    setColor(blackbody(i*30));
    usleep(10000);
  }

  return 0;
}
