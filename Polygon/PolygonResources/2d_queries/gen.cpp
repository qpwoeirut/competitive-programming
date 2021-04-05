#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;

const int MN = 1e3;
const int MQ = 1e6;
const int MIN_VAL = -1e9;
const int MAX_VAL = 1e9;

int N, M, Q;
int G[MN][MN];
int qtype[MQ], qr[MQ], qc[MQ], qx[MQ];

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    Q = atoi(argv[3]);

    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            G[i][j] = rnd.next(MIN_VAL, MAX_VAL);
        }
    }
    for (int i=0; i<Q; ++i) {
        qtype[i] = rnd.next(1, 2);
        qr[i] = rnd.next(1, N);
        qc[i] = rnd.next(1, M);
        qx[i] = rnd.next(MIN_VAL, MAX_VAL);
    }

    cout << N << ' ' << M << ' ' << Q << '\n';
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            if (j) cout << ' ';
            cout << G[i][j];
        }
        cout << '\n';
    }

    if (count(qtype, qtype+Q, 2) == 0) {
        qtype[Q-1] = 2;
    }
    for (int i=0; i<Q; ++i) {
        cout << qtype[i] << ' ' << qr[i] << ' ' << qc[i];
        if (qtype[i] == 1) {
            cout << ' ' << qx[i];
        }
        cout << '\n';
    }
}

