// UNFINISHED

#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

const int MN = 200;

int N, MIN_VAL, MAX_VAL;
int G[MN][MN];

void random_graph() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {

        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int graph_type = atoi(argv[1]);
    N = atoi(argv[2]);
    MIN_VAL = atoi(argv[3]);
    MAX_VAL = atoi(argv[4]);

    if (array_type == 0) {
        random_graph();
    } else assert(false);

    cout << N << '\n';
    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << A[i];
    }
    cout << '\n';
}


