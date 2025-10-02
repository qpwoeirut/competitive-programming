#!/bin/bash
set -e

g++-15 -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -O3 -Wall "$1/BridgeRunners.cpp" -o "BridgeRunners.out"
#clang++ -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL "$1/BridgeRunners.cpp" -o "BridgeRunners.out"
java -jar "tester.jar" -exec "./BridgeRunners.out" -seed "$2"
rm BridgeRunners.out
