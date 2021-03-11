#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MN = 1e7;

int N, MIN_VAL, MAX_VAL;
int A[MN];

void random_array() {
    for (int i=0; i<N; ++i) {
        A[i] = rnd.next(MIN_VAL, MAX_VAL);
    }
}

void array_all_same(int val) {
    fill(A, A+N, val);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int array_type = atoi(argv[1]);
    N = atoi(argv[2]);
    MIN_VAL = atoi(argv[3]);
    MAX_VAL = atoi(argv[4]);

    if (array_type == 0) {
        random_array();
    } else if (array_type == 1) {
        array_all_same(MIN_VAL);
    } else if (array_type == 2) {
        array_all_same(MAX_VAL);
    } else assert(false);

    cout << N << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << '\n';
}


