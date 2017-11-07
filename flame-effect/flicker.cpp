#include <math.h>

float slowFlicker (unsigned int timeMs) {
  return 0.6f
    + 0.1f*sinf(timeMs/31.0f)
    + 0.1f*sinf(timeMs/53.0f)
    + 0.1f*sinf(timeMs/753.0f)
    + 0.1f*sinf(timeMs/1717.0f);
}

float midFlicker (unsigned int timeMs) {
  return 0.6f
    + 0.1f*sinf(timeMs/19.0f)
    + 0.1f*sinf(timeMs/31.0f)
    + 0.1f*sinf(timeMs/73.0f)
    + 0.05f*sinf(timeMs/753.0f)
    + 0.05f*sinf(timeMs/1717.0f);
}

float fastFlicker (unsigned int timeMs) {
  return 0.6f
    + 0.1f*sinf(timeMs/11.0f)
    + 0.1f*sinf(timeMs/17.0f)
    + 0.1f*sinf(timeMs/31.0f)
    + 0.05f*sinf(timeMs/753.0f)
    + 0.05f*sinf(timeMs/1717.0f);
}
