//bus_terminals.cpp created at 08/28/23 19:43:36
// wrong but hopefully gets partials

#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;
using pii=pair<int,int>;

const int MN = 500;
const int INF = 1e9;

const int MOD = (1 << 15) - 1;

inline int dist(const int a, const int b) {
    return abs((a >> 15) - (b >> 15)) + abs((a & MOD) - (b & MOD));
}

int N;
int A[MN];
int da[MN], db[MN];
bitset<MN> used;

int hub_a[MN], hub_b[MN];
int n_a, n_b;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        int x, y;
        cin >> x >> y;
        A[i] = (x << 15) | y;
    }

    int ans = INF;
    for (int a=0; a<N; ++a) {
        for (int b=a+1; b<N; ++b) {
            for (int i=0; i<N; ++i) {
                da[i] = (dist(A[a], A[i]) << 15) | i;
                db[i] = (dist(A[b], A[i]) << 15) | i;
            }
            sort(da, da+N);
            sort(db, db+N);
            //for (int i=0; i<N; ++i) { cerr << '[' << da[i].val << ' ' << da[i].idx << "] [" << db[i].val << ' ' << db[i].idx << "]\n"; }

            used.reset();
            n_a = n_b = 0;
            int ia = 0, ib = 0;
            while (ia < N && ib < N) {
                //cerr << ia << ' ' << ib << ' ' << hub_a.size() << ' ' << hub_b.size() << endl;
                if (da[ia] <= db[ib]) {
                    if (!used[da[ia] & MOD]) {
                        used[da[ia] & MOD] = true;
                        hub_a[n_a++] = da[ia];
                    }
                    ++ia;
                } else {
                    if (!used[db[ib] & MOD]) {
                        used[db[ib] & MOD] = true;
                        hub_b[n_b++] = db[ib];
                    }
                    ++ib;
                }
            }
            //cerr << "a\n"; for (pii p: hub_a) { cerr << '[' << p.val << ' ' << p.idx << "] "; } cerr << endl;
            //cerr << "b\n"; for (pii p: hub_b) { cerr << '[' << p.val << ' ' << p.idx << "] "; } cerr << endl;
            sort(hub_a, hub_a + n_a);
            sort(hub_b, hub_b + n_b);

            const int a0 = n_a >= 1 ? (hub_a[n_a - 1] >> 15) : -INF;
            const int a1 = n_a >= 2 ? (hub_a[n_a - 2] >> 15) : -INF;
            const int b0 = n_b >= 1 ? (hub_b[n_b - 1] >> 15) : -INF;
            const int b1 = n_b >= 2 ? (hub_b[n_b - 2] >> 15) : -INF;

            const int cur = max({a0 + a1, a0 + dist(A[a], A[b]) + b0, b0 + b1});
            ans = min(ans, cur);
        }
    }

    cout << ans << '\n';
}

