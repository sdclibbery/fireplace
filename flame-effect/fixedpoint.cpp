unsigned char fp8Mul (unsigned char l, unsigned char r) {
  unsigned long out = (unsigned long)l * (unsigned long)r;
  return (unsigned char)(out/255);
}

static unsigned char cosQ1 (unsigned char x) {
  return 255 - ((unsigned long)x*x)/32;
}

unsigned char fp8Cos (unsigned char x) {
  unsigned char quadrant = x/64;
  unsigned char v = x % 64;
  switch (quadrant) {
    case 0:
      return cosQ1(v);
    case 1:
      return 255-cosQ1(63-v);
    case 2:
      return 255-cosQ1(v);
    case 3:
      return cosQ1(63-v);
  }
}
