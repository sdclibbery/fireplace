#!/bin/bash
# Build as a local executable to allow testing the flame effect
# Run in a git prompt on windows

gcc flametest.cpp flamecolour.cpp rgb.cpp flicker.cpp fixedpoint.cpp -lm -o flametest.exe
./flametest.exe
