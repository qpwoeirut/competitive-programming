g++-11 -std=c++20 -O3 -Wall -funroll-loops -I /usr/local/include experiment.cpp -o experiment.out
echo "Compiled!"
./experiment.out
rm experiment.out

