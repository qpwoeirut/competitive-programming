g++-10 -std=c++17 -O2 -lm -Wall -DLOCAL digit_blocks.cpp -o digit_blocks.out
python3 interactive_runner.py python3 digit_blocks_tester.py 1 -- ./digit_blocks.out
