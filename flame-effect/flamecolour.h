#pragma once
#include "rgb.h"

typedef Rgb (*FlameFunction)(unsigned long);

Rgb woodFlame (unsigned long time);
Rgb embersFlame (unsigned long time);
Rgb gasFlame (unsigned long time);
Rgb halloweenFlame (unsigned long time);
Rgb rainbowFlame (unsigned long time);
Rgb crystalFlame (unsigned long time);
