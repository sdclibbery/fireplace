#include "fixedpoint.h"

float slowFlicker (unsigned int timeMs) {
  unsigned char out = 32
    + fp8Mul(48, fp8Cos(timeMs*40/31))
    + fp8Mul(64, fp8Cos(timeMs*40/53))
    + fp8Mul(64, fp8Cos(timeMs*40/753))
    + fp8Mul(48, fp8Cos(timeMs*40/1717));
  return out/255.0f;
}

float midFlicker (unsigned int timeMs) {
  unsigned char out = 32
    + fp8Mul(48, fp8Cos(timeMs*40/19))
    + fp8Mul(64, fp8Cos(timeMs*40/31))
    + fp8Mul(48, fp8Cos(timeMs*40/73))
    + fp8Mul(32, fp8Cos(timeMs*40/753))
    + fp8Mul(32, fp8Cos(timeMs*40/1717));
  return out/255.0f;
}

float fastFlicker (unsigned int timeMs) {
  unsigned char out = 32
    + fp8Mul(48, fp8Cos(timeMs*40/11))
    + fp8Mul(32, fp8Cos(timeMs*40/17))
    + fp8Mul(32, fp8Cos(timeMs*40/31))
    + fp8Mul(16, fp8Cos(timeMs*40/753))
    + fp8Mul(16, fp8Cos(timeMs*40/1717));
  return out/255.0f;
}
