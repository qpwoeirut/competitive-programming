#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using ll=long long;
using pt=complex<ll>;
using pii=pair<ll,ll>;

const int MN = 1003;

int N;
pt A[MN];
int B[MN];
int par[MN];
pii threat[MN];
int th_idx[MN];

int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
void join(const int u, const int v) {
    const int ru = root(u), rv = root(v);
    par[rv] = par[v] = ru;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        int x, y;
        cin >> x >> y >> B[i];
        A[i] = pt(x, y);

        par[i] = i;
    }

    for (int i=0; i<N; ++i) {
        threat[i] = pii(0, 1);
        th_idx[i] = -1;
        for (int j=0; j<N; ++j) {
            if (i == j) continue;

            pii cur(B[j], norm(A[i] - A[j]));
            if (cur.fi * threat[i].se > threat[i].fi * cur.se) {
                threat[i] = cur;
                th_idx[i] = j;
            } else if (cur.fi * threat[i].se == threat[i].fi * cur.se) {
                th_idx[i] = -1;
            }
        }

        if (th_idx[i] != -1 && threat[i].fi > B[i] * threat[i].se) {
            join(th_idx[i], i);
        }
    }

    for (int i=0; i<N; ++i) {
        if (threat[i].fi <= B[i] * threat[i].se) {
            cout << "K\n";
        } else if (th_idx[i] == -1) {
            cout << "D\n";
        } else {
            cout << root(i) + 1 << '\n';
        }
    }
}
/*
5
2 5 14
2 3 2
3 2 7
1 1 2
2 1 3

*/
