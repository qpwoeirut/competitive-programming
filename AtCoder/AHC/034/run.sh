#!/bin/zsh

g++-13 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -O2 -lm -Wall -DLOCAL $1.cpp -o $1.out
#g++-13 -std=c++20 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL $1.cpp -o $1.out

mkdir out
for i in {0000..0009}
do
    echo $i
    ./$1.out < "in/$i.txt" > "out/$i.txt"
done

rm $1.out

