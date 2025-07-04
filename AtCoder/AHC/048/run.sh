#!/bin/zsh

set -e

#g++-14 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -O2 -lm -Wall $1.cpp -o $1.out
#g++-14 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -O2 -lm -Wall -DLOCAL $1.cpp -o $1.out
#clang++ -std=c++20 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv $1.cpp -o $1.out
clang++ -std=c++20 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL $1.cpp -o $1.out

for i in {0000..0099}; do
    echo "Running case $i"
    time "./$1.out" < "in/$i.txt" > "out/$i.txt"
done

