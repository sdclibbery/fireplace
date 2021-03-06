#pragma once

static inline unsigned char fp8Mul (unsigned char l, unsigned char r) {
  unsigned long out = (unsigned long)l * (unsigned long)r;
  return (unsigned char)(out/255);
}

static inline unsigned char fp8CosQ1 (unsigned char x) {
  return 255 - ((unsigned long)x*x)/32;
}

static inline unsigned char fp8Cos (unsigned char x) {
  unsigned char quadrant = x/64;
  unsigned char v = x % 64;
  switch (quadrant) {
    case 0:
      return fp8CosQ1(v);
    case 1:
      return 255-fp8CosQ1(63-v);
    case 2:
      return 255-fp8CosQ1(v);
    default:
      return fp8CosQ1(63-v);
  }
}
