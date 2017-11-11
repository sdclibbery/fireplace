#include <math.h>
#include "fixedpoint.h"

float slowFlicker (unsigned int timeMs) {
  return 0.6f
    + 0.1f*sinf(timeMs/31.0f)
    + 0.1f*sinf(timeMs/53.0f)
    + 0.1f*sinf(timeMs/753.0f)
    + 0.1f*sinf(timeMs/1717.0f);
}

float midFlicker (unsigned int timeMs) {
  unsigned char out = 128
    + fp8Mul(32, fp8Cos(timeMs*255/19))
    + fp8Mul(32, fp8Cos(timeMs*255/31))
    + fp8Mul(32, fp8Cos(timeMs*255/73))
    + fp8Mul(16, fp8Cos(timeMs*255/753))
    + fp8Mul(16, fp8Cos(timeMs*255/1717));
  return out/255.0f;
}

float fastFlicker (unsigned int timeMs) {
  return 0.6f
    + 0.1f*sinf(timeMs/11.0f)
    + 0.1f*sinf(timeMs/17.0f)
    + 0.1f*sinf(timeMs/31.0f)
    + 0.05f*sinf(timeMs/753.0f)
    + 0.05f*sinf(timeMs/1717.0f);
}
