#pragma once
#include "rgb.h"

typedef Rgb (*FlameFunction)(unsigned char);

Rgb woodFlame (unsigned char intensity);
Rgb embersFlame (unsigned char intensity);
Rgb gasFlame (unsigned char intensity);
Rgb halloweenFlame (unsigned char intensity);
Rgb rainbowFlame (unsigned char intensity);
Rgb crystalFlame (unsigned char intensity);
