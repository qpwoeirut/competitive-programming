g++-11 -std=c++17 -Wl,-stack_size -Wl,0x10000000 -O2 -lm -Wall -I /usr/local/Cellar/boost/1.78.0_1/include -DLOCAL brute.cpp -o brute.out
echo "Compiled!"
time ./brute.out
rm brute.out

