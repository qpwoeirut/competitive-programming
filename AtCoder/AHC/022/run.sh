#!/bin/zsh

g++-12 -std=c++17 -I ~/CompetitiveProgramming/setupFiles -O2 -lm -Wall -DLOCAL sol.cpp -o sol.out
#g++-12 -std=c++17 -I ~/CompetitiveProgramming/setupFiles -g -lm -Wall -fsanitize=address,undefined,signed-integer-overflow -ftrapv -DLOCAL sol.cpp -o sol.out

cd tools
mkdir out
for i in {0000..0099}
do
    cargo run --release --bin tester ../sol.out < "in/$i.txt" > "out/$i.txt"
#    cargo run --release --bin tester ../sol.out < "in_S1/$i.txt" > "out/$i.txt"
#    cargo run --release --bin tester ../sol.out < "in_S400/$i.txt" > "out/$i.txt"
#    cargo run --release --bin tester ../sol.out < "in_S900/$i.txt" > "out/$i.txt"
#    cargo run --release --bin tester ../sol.out < "in_dense/$i.txt" > "out/$i.txt"
done

cd ..
rm sol.out
