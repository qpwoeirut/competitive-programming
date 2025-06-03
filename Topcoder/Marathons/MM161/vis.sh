set -e

#clang++ -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -g -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL "$1/HordeChess.cpp" -o "HordeChess.out"
g++-14 -std=gnu++11 -I ~/CompetitiveProgramming/setupFiles -O3 -Wall "$1/HordeChess.cpp" -o "HordeChess.out"

java -jar "tester.jar" -exec "./HordeChess.out" -seed "$2" -debug -pr -delay 0
