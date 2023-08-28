g++-12 -std=c++20 -O3 -funroll-loops -mavx2 -mtune=native xor.cpp -o xor.out
./xor.out
rm xor.out
