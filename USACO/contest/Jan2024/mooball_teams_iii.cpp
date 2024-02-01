#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
using ll=long long;

#define x first
#define y second

const int MN = 200005;
const int MOD = 1e9 + 7;

int N;
pii A[MN];

int BIT[MN];
void inc(int idx) {
    for (; idx < MN; idx+=(idx & -idx)) ++BIT[idx];
}
int query(int idx) {
    int ret = 0;
    for (; idx > 0; idx-=(idx & -idx)) ret += BIT[idx];
    return ret;
}

ll p2[MN];

int solve() {
    p2[0] = 1;
    for (int i=1; i<=N; ++i) {
        p2[i] = (p2[i - 1] * 2) % MOD;
    }

    ll hori_ct = 0;
    for (int i=0; i<N; ++i) {
        const int R = A[i].y;
        const int B = N - A[i].y;

        hori_ct += ((p2[R - 1]) * (p2[B] - 1)) % MOD;
    }
    hori_ct %= MOD;

    ll vert_ct = 0;
    ll duplicates = 0;
    for (int i=0; i<N; ++i) {
        const int R = A[i].x;
        const int B = N - A[i].x;

        vert_ct += ((p2[R - 1]) * (p2[B] - 1)) % MOD;
    }
    vert_ct %= MOD;

    for (int i=0; i<N; ++i) {
        inc(A[i].y);
        const int BL = query(A[i].y - 1);
        const int TL = A[i].x - BL - 1;
        const int BR = A[i].y - BL - 1;
        const int TR = N - BL - TL - BR - 1;

        duplicates += p2[BL] * (p2[TR] - 1);
        duplicates += p2[TL] * (p2[BR] - 1);
        duplicates %= MOD;

        //cerr << i << ' ' << j << ' ' << duplicates << endl;
    }

    cerr << hori_ct << ' ' << vert_ct << ' ' << duplicates << endl;

    ll ans = ((hori_ct + vert_ct - duplicates) * 2) % MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

int recurse(int i, int mn_x1, int mx_x1, int mn_y1, int mx_y1, int mn_x2, int mx_x2, int mn_y2, int mx_y2) {
    if (i == N) {
        return mn_x1 != MN && mn_x2 != MN && (mx_x1 < mn_x2 || mx_x2 < mn_x1 || mx_y1 < mn_y2 || mx_y2 < mn_y1);
    }

    return recurse(i + 1, mn_x1, mx_x1, mn_y1, mx_y1, mn_x2, mx_x2, mn_y2, mx_y2) +
        recurse(i + 1, min(mn_x1, A[i].x), max(mx_x1, A[i].x), min(mn_y1, A[i].y), max(mx_y1, A[i].y), mn_x2, mx_x2, mn_y2, mx_y2) +
        recurse(i + 1, mn_x1, mx_x1, mn_y1, mx_y1, min(mn_x2, A[i].x), max(mx_x2, A[i].x), min(mn_y2, A[i].y), max(mx_y2, A[i].y));
}

int brute() {
    return recurse(0, MN, 0, MN, 0, MN, 0, MN, 0);
}

int yval[MN];
void test() {
    mt19937 rng(8);
    for (N=4; N<=10; ++N) {
        for (int i=0; i<N; ++i) yval[i] = i;
        for (int t=0; t<1000000; ++t) {
            shuffle(yval, yval+N, rng);
            for (int i=0; i<N; ++i) {
                A[i] = pii(i + 1, yval[i] + 1);
            }

            int sans = solve();
            int bans = brute();
            if (bans != sans) {
                cout << N << endl;
                for (int i=0; i<N; ++i) {
                    cout << A[i].x << ' ' << A[i].y << endl;
                }
                cout << "ans: " << bans << ' ' << sans << endl;
            }
            assert(bans == sans);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
    }
    sort(A, A+N);
    cout << (N <= 18 ? brute() : solve()) << '\n';
}
