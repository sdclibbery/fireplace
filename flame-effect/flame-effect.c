#include <stdio.h>
#include <unistd.h>

/*
ToDO
- Not working: its printing to nearest colour not true color :-(
*/

static void printColouredBlock (unsigned char r, unsigned char g, unsigned char b) {
  printf("\x1b[38;2;%d;%d;%dm\u2588\u2588\x1b[0m", r, g, b);
}

static void setColor (unsigned char r, unsigned char g, unsigned char b) {
  printf("\x08\x08");
  printColouredBlock(r, g, b);
}

int main () {
  printColouredBlock(0,0,0);

  for (unsigned char i=0; i<255; i++) {
    setColor(i,i,i);
    usleep(50000);
  }

  return 0;
}
