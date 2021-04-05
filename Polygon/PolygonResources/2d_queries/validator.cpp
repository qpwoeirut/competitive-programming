#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

const int MIN_N = 1;
const int MAX_N = 500;
const int MIN_Q = 1;
const int MAX_Q = 5e5;
const int MIN_VAL = -1e9;
const int MAX_VAL = 1e9;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int N = inf.readInt(MIN_N, MAX_N, "n");
    inf.readSpace();
    int M = inf.readInt(MIN_N, MAX_N, "m");
    inf.readSpace();
    int Q = inf.readInt(MIN_Q, MAX_Q, "q");
    inf.readEoln();

    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            if (j > 0) inf.readSpace();
            inf.readInt(MIN_VAL, MAX_VAL, "a_rc"); // change to readLong if values can be longs
        }
        inf.readEoln();
    }

    bool has_type_2 = false;
    for (int i=0; i<Q; i++) {
        int t = inf.readInt(1, 2, "t");
        inf.readSpace();
        inf.readInt(1, N, "r");
        inf.readSpace();
        inf.readInt(1, M, "c");
        if (t == 1) {
            inf.readSpace();
            inf.readInt(MIN_VAL, MAX_VAL, "x");
        } else {
            has_type_2 = true;
        }
        inf.readEoln();
    }
    inf.readEof();

    ensuref(has_type_2, "need at least one query of type 2");
}

