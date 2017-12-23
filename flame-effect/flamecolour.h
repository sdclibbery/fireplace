#pragma once
#include "rgb.h"

typedef Rgb (*FlameFunction)(unsigned char, unsigned long);

Rgb woodFlame (unsigned char fractionalPosition, unsigned long time);
Rgb embersFlame (unsigned char fractionalPosition, unsigned long time);
Rgb gasFlame (unsigned char fractionalPosition, unsigned long time);
Rgb halloweenFlame (unsigned char fractionalPosition, unsigned long time);
Rgb rainbowFlame (unsigned char fractionalPosition, unsigned long time);
Rgb crystalFlame (unsigned char fractionalPosition, unsigned long time);
Rgb purpleBlingFlame (unsigned char fractionalPosition, unsigned long time);
