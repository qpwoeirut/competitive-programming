//kutije.cpp created at 12/23/21 17:40:43

#include <bits/stdc++.h>

using namespace std;

const int MN = 1003;

int N, M, Q;

int par[MN];
int sz[MN];

int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;
    if (sz[ru] < sz[rv]) swap(ru, rv);
    par[rv] = par[v] = ru;
    sz[ru] += sz[rv];
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> Q;
    
    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    for (int i=0; i<M; ++i) {
        for (int u=0; u<N; ++u) {
            int v;
            cin >> v;
            --v;
            join(u, v);
        }
    }

    for (int i=0; i<Q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;

        cout << (root(a) == root(b) ? "DA" : "NE") << '\n';
    }
}
