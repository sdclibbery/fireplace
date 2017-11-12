#!/bin/bash
# Build as a local executable to allow testing the flame effect
# Run in a git prompt on windows

gcc flametest.cpp flamecolour.cpp flicker.cpp -lm -o flametest.exe
./flametest.exe
