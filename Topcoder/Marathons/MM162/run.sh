#!/bin/bash
set -e

g++-14 -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -O3 -Wall "$1/DaylightRobbery.cpp" -o "DaylightRobbery.out"
#clang++ -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL "$1/DaylightRobbery.cpp" -o "DaylightRobbery.out"
java -jar "tester.jar" -exec "./DaylightRobbery.out" -seed "$2" -pr -novis
rm DaylightRobbery.out
