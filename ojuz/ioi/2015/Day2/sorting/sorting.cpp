#include "sorting.h"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

const int MN = 200005;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    //cin >> N; for (int i=0; i<N; ++i) cin >> S[i];

    if (is_sorted(S, S+N)) return 0;
    int K = 0;

    if (X[0] == 0 && Y[0] == 0) {
        for (int i=0; i<N; ++i) {
            int idx = min_element(S+i, S+N) - S;
            assert(i <= idx && idx < N);
            if (idx == i) continue;
            P[K] = i;
            Q[K] = idx;
            ++K;
            swap(S[i], S[idx]);
        }
    } else if (X[0] == 0 && Y[0] == 1) {
        for (int i=2; i<N; ++i) {
            int idx = min_element(S+i, S+N) - S;
            assert(i <= idx && idx < N);
            if (idx == i) continue;
            swap(S[0], S[1]);
            //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;

            swap(S[i], S[idx]);
            P[K] = i;
            Q[K] = idx;
            ++K;
            //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;
        }
        while (N > 2 && S[0] + S[1] > 1) {
            swap(S[0], S[1]);
            //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;

            if (S[0] < S[1]) {
                P[K] = 1;
                swap(S[1], S[2]);
            } else {
                P[K] = 0;
                swap(S[0], S[2]);
            }
            Q[K] = 2;
            ++K;
            //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;

            for (int i=2; i+1<N; ++i) {
                if (S[i] > S[i+1]) {
                    swap(S[0], S[1]);
                    //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;

                    swap(S[i], S[i+1]);
                    P[K] = i;
                    Q[K] = i+1;
                    ++K;
                    //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;
                } else break;
            }
        }

        if (S[0] == 1) {
            assert(S[1] == 0);
            swap(S[0], S[1]);
            //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;

            P[K] = 0;
            Q[K] = 0;
            ++K;
            //for (int j=0; j<N; ++j) { cerr << S[j] << ' '; } cerr << endl;
        }
    } else assert(0);

    //for (int i=0; i<N; ++i) { cerr << S[i] << ' '; } cerr << endl;
    assert(is_sorted(S, S+N));

    assert(K <= M);
    //cout << K << endl; for (int i=0; i<K; ++i) { cout << P[i] << ' ' << Q[i] << '\n'; }
    return K;
}

