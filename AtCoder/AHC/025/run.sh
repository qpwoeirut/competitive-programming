#!/bin/zsh

g++-12 -std=c++17 -I ~/CompetitiveProgramming/setupFiles -O2 -lm -Wall -DLOCAL $1.cpp -o $1.out
#g++-12 -std=c++17 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL $1.cpp -o $1.out

mkdir out
for i in {0000..0099}
do
    cargo run -q -r --manifest-path=tools/Cargo.toml --bin tester ./$1.out < "in_Q900/$i.txt" > "out/$i.txt"
done

rm $1.out
