#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

const int MN = 1001001;

int N, M;
pii edge[MN];

int par[MN];
int sz[MN];

int root(int u) {
    if (par[u] == u) return u;
    par[u] = root(par[u]);
    return par[u];
}

bool join(int u, int v) {
    int ru = root(u);
    int rv = root(v);
    if (ru == rv) return false;
    if (sz[ru] < sz[rv]) {
        swap(ru, rv);
        swap(u, v);
    }
    sz[ru] += sz[rv];
    par[u] = par[v] = par[rv] = ru;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edge[i] = pii(u, v);
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    if (N == 1) {
        cout << "0\n";
        return 0;
    }

    int comps = N;
    for (int i=0; i<M; ++i) {
        comps -= join(edge[i].first, edge[i].second);
        if (comps == 1) {
            cout << i + 1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}
