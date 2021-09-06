//double_move.cpp created at 09/05/21 23:53:39

#include <bits/stdc++.h>

using namespace std;

const int MN = 36;

int N, K;
int A[MN], B[MN];

bitset<MN> used;
int sim(int M) {
    int wins = 0;
    for (int m=0; m<(1<<(M+1)); ++m) {
        used.reset();
        for (int j=0; j<=M; ++j) {
            int take;
            if ((m >> j) & 1) take = A[j];
            else take = B[j];
            if (used[take]) {
                wins += (M + j) & 1;
                break;
            } else {
                used[take] = true;
            }
        }
    }
    return wins;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<K; ++i) {
        cin >> A[i] >> B[i];
        --A[i]; --B[i];
    }

    for (int i=K; i<=N; ++i) {
        int best = -1, ba = -1, bb = -1;
        for (A[i]=0; A[i]<N; ++A[i]) {
            for (B[i]=0; B[i]<N; ++B[i]) {
                int wins = sim(i);
                if (wins > best) {
                    best = wins;
                    ba = A[i];
                    bb = B[i];
                }
            }
        }
        A[i] = ba;
        B[i] = bb;
    }

    int alice = sim(N);
    int bob = (1 << (N + 1)) - alice;
    if (N & 1) {
        swap(alice, bob);
    }
    cout << alice << ' ' << bob << '\n';

    for (int i=0; i<=N; ++i) {
        cerr << A[i] << ' ' << B[i] << endl;
    }
}
