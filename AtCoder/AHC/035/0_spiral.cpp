#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

#include <bits/stdc++.h>

using namespace std;

const int N = 6;
const int M = 15;
const int T = 10;
const int K = 2 * N * (N - 1);

int X[K][M];
int A[N][N];

int idxs[K];

int score(int idx) {
    int s = 0;
    for (int i=0; i<M; ++i) s += X[idx][i];
    return s;
}

const int chr[4] = {0, 1, 0, -1};
const int chc[4] = {1, 0, -1, 0};
void place_spiral() {
    int d = 0;
    int r1 = 0, r2 = N - 1;
    int c1 = 0, c2 = N - 1;

    int r = 0, c = 0;
    for (int i=N*N-1; i>=0; --i) {
        if (d == 0 && c == c2) {
            d = 1;
            ++r1;
        } else if (d == 1 && r == r2) {
            d = 2;
            --c2;
        } else if (d == 2 && c == c1) {
            d = 3;
            --r2;
        } else if (d == 3 && r == r1) {
            d = 0;
            ++c1;
        }

        A[r][c] = idxs[i];
        r += chr[d];
        c += chc[d];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int _N, _M, _T;
    cin >> _N >> _M >> _T;
    assert(N == _N && M == _M && T == _T);

    for (int i=0; i<K; ++i) idxs[i] = i;

    for (int t=0; t<T; ++t) {
        for (int i=0; i<K; ++i) {
            for (int j=0; j<M; ++j) {
                cin >> X[i][j];
            }
        }

        sort(idxs, idxs+K, [](const int ia, const int ib) { return score(ia) > score(ib); });
        place_spiral();

        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                cout << A[i][j] << (j+1 < N ? ' ' : '\n');
            }
        }
        cout.flush();
    }
}
