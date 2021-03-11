#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MIN_N = 1;
const int MAX_N = 1e8;

const int MIN_VAL = -1e9;
const int MAX_VAL = 1e9;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "n");
    inf.readEoln();

    for (int i=0; i<N; i++) {
        if (i > 0) inf.readSpace();
        inf.readInt(MIN_VAL, MAX_VAL, "a_i"); // change to readLong if values can be longs
    }
    inf.readEoln();
    inf.readEof();
}
