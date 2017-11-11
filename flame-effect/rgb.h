typedef struct Rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Rgb;

Rgb rgbScale (Rgb c, unsigned char scale);
Rgb rgbAdd (Rgb l, Rgb r);
Rgb rgbLerp (Rgb lo, Rgb hi, unsigned char x);
