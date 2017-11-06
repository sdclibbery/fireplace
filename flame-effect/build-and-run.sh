#!/bin/bash
# Build as a local executable to allow testing the flame effect
# Run in a git prompt on windows

gcc flametest.c blackbody.c -lm -o flametest.exe
./flametest.exe
