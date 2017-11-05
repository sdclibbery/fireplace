#include <stdio.h>

static void printColouredBlock (unsigned char r, unsigned char g, unsigned char b) {
  printf("\x1b[38;2;%d;%d;%dm\xdb\xdb\x1b[0m", r, g, b);
}

static void setColor (unsigned char r, unsigned char g, unsigned char b) {
  printf("\x08\x08");
  printColouredBlock(r, g, b);
}

int main () {
  printColouredBlock(0,0,0);
  setColor(2, 255, 100);
  setColor(255, 255, 100);
  setColor(2, 2, 100);
  setColor(250, 2, 1);
  return 0;
}
