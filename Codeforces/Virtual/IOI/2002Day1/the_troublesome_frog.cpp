//the_troublesome_frog.cpp created at 08/27/23 15:49:45

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
#define row first
#define col second

const int MN = 5000;
const int INF = 1001001001;

int R, C;
int N;
pii A[MN];
bitset<MN> G[MN];

inline bool in_bounds(const int r, const int c) { return 0 <= r && r < R && 0 <= c && c < C; }

int ans;
void check(const pii& a, const pii& b) {
    const int dr = b.row - a.row;
    assert(dr >= 0);
    const int dc = b.col - a.col;

    const bool sub = !in_bounds(b.row + dr, b.col + dc);
    const bool add = !in_bounds(a.row - dr, a.col - dc);

    int k;
    bool ok = true;
    if (sub) {
        const int kr = dr == 0 ? INF : a.row / dr;
        const int kc = dc == 0 ? INF : (dc < 0 ? (C - a.col - 1) / -dc : (a.col / +dc));
        const int maxk = min(kr, kc);
        if (maxk + 1 < ans || G[a.row - dr * maxk][a.col - dc * maxk] == false) ok = false;

        for (k = 1; ok && in_bounds(a.row - dr * k, a.col - dc * k); ++k) {
            ok &= G[a.row - dr * k][a.col - dc * k];
        }
    } else if (add) {
        const int kr = dr == 0 ? INF : (R - b.row - 1) / dr;
        const int kc = dc == 0 ? INF : (dc > 0 ? (C - b.col - 1) / +dc : (b.col / -dc));
        const int maxk = min(kr, kc);
        if (maxk + 1 < ans || G[b.row + dr * maxk][b.col + dc * maxk] == false) ok = false;

        for (k = 1; ok && in_bounds(b.row + dr * k, b.col + dc * k); ++k) {
            ok &= G[b.row + dr * k][b.col + dc * k];
        }
    } else ok = false;

    ++k;
    if (ok && ans < k && k >= 3) {
        ans = k;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> R >> C;
    cin >> N;

    for (int i=0; i<N; ++i) {
        cin >> A[i].row >> A[i].col; --A[i].row; --A[i].col;
        G[A[i].row][A[i].col] = true;
    }
    sort(A, A+N);

    for (int i=0; i<N; ++i) {
        for (int j=i+1; j<N; ++j) {
            check(A[i], A[j]);
        }
    }

    cout << ans << '\n';
}

