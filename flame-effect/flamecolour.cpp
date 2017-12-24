#include <math.h>
#include "fixedpoint.h"
#include "rgb.h"

static inline unsigned char constant (unsigned char v) {
  return v;
}
static inline unsigned char sqr (unsigned char x) {
  return fp8Mul(x, x);
}
static inline unsigned char invSqr (unsigned char x) {
  return 255 - fp8Mul((255-x), (255-x));
}
static inline unsigned char up (unsigned char x, unsigned char from, unsigned char to) {
  return from + fp8Mul(x, to - from);
}
static inline unsigned char down (unsigned char x, unsigned char from, unsigned char to) {
  return to + fp8Mul(255-x, from-to);
}
static unsigned char flicker (unsigned long time) {
  return 32
    + fp8Mul(48, fp8Cos(time/19))
    + fp8Mul(64, fp8Cos(time/31))
    + fp8Mul(48, fp8Cos(time/73))
    + fp8Mul(32, fp8Cos(time/753))
    + fp8Mul(32, fp8Cos(time/1717));
}
static unsigned long randomise (unsigned char pos) {
  return pos*0x17346547;
}

Rgb woodFlame (unsigned char fractionalPosition, unsigned long time) {
  unsigned char intensity = flicker(time+randomise(fractionalPosition));
  Rgb rgb = {
    constant(255),
    up(sqr(intensity), 32, 120),
    constant(0),
  };
  return rgbScale(rgb, intensity);
}

Rgb embersFlame (unsigned char fractionalPosition, unsigned long time) {
  unsigned char intensity = flicker(time+randomise(fractionalPosition));
  Rgb rgb = {
    constant(255),
    up(sqr(sqr(intensity)), 0, 80),
    constant(0),
  };
  return rgbScale(rgb, intensity/3);
}

Rgb gasFlame (unsigned char fractionalPosition, unsigned long time) {
  unsigned char intensity = flicker(time+randomise(fractionalPosition));
  Rgb rgb = {
    up(intensity, 0, 255),
    up(sqr(intensity), 0, 160),
    down(invSqr(intensity), 255, 0),
  };
  return rgbScale(rgb, intensity);
}

Rgb halloweenFlame (unsigned char fractionalPosition, unsigned long time) {
  unsigned char intensity = flicker(time+randomise(fractionalPosition));
  Rgb rgb = {
    constant(0),
    up(invSqr(intensity), 0, 200),
    down(invSqr(intensity), 255, 0),
  };
  return rgbScale(rgb, intensity);
}

Rgb crystalFlame (unsigned char fractionalPosition, unsigned long time) {
  unsigned long randomisedTime = time/7+randomise(fractionalPosition);
  if (randomisedTime%1000 == 0) {
    static Rgb white = {255, 255, 255};
    return white;
  }
  Rgb rgb = {
    constant(60),
    down(fp8Cos(randomisedTime), 65, 50),
    up(fp8Cos(randomisedTime), 55, 70),
  };
  return rgb;
}

Rgb rainbowFlame (unsigned char fractionalPosition, unsigned long time) {
  Rgb rgb = {
    fp8Cos(time/31+fractionalPosition),
    fp8Cos(time/31+85+fractionalPosition),
    fp8Cos(time/31+170+fractionalPosition),
  };
  return rgb;
}

Rgb purpleBlingFlame (unsigned char fractionalPosition, unsigned long time) {
  if (fp8Cos(time/37-fractionalPosition*2) > 200) {
    unsigned char silverAmount = up(fp8Cos(time/29+fractionalPosition), 190, 255);
    Rgb rgb = { silverAmount, silverAmount, silverAmount };
    return rgb;
  } else {
    unsigned char purpleAmount = fp8Cos(time/31+fractionalPosition);
    Rgb rgb = {
      up(purpleAmount, 140, 190),
      0,
      up(purpleAmount, 120, 220)
    };
    return rgb;
  }
}
