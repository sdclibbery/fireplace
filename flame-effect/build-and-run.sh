#!/bin/bash
# Build as a local executable to allow testing the flame effect
# Run in a git prompt on windows

g++ -std=c++11 flametest.cpp flamecolour.cpp flicker.cpp fireplace.cpp -lm -o flametest.exe
./flametest.exe
