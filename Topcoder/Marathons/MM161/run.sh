set -e

g++-14 -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -O3 -Wall "$1/HordeChess.cpp" -o "HordeChess.out"
java -jar "tester.jar" -exec "./HordeChess.out" -seed "$2" -novis -pr
