#include "fixedpoint.h"

unsigned char flicker (unsigned int speed, unsigned long timeMs) {
  return 32
    + fp8Mul(48, fp8Cos(timeMs*speed/19))
    + fp8Mul(64, fp8Cos(timeMs*speed/31))
    + fp8Mul(48, fp8Cos(timeMs*speed/73))
    + fp8Mul(32, fp8Cos(timeMs*speed/753))
    + fp8Mul(32, fp8Cos(timeMs*speed/1717));
}
