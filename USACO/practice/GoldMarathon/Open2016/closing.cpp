#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, M;
int A[MN];
bool ans[MN];
bool in[MN];
set<int> adj[MN];

int par[MN];
int sz[MN];
int root(const int u) {
    if (par[u] != u) {
        par[u] = root(par[u]);
    }
    return par[u];
}

set<int> roots;
void join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    par[rv] = ru;
    sz[ru] += sz[rv];
    roots.erase(rv);
}

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for (int i=N-1; i>=0; --i) {
        cin >> A[i];
        --A[i];
    }

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
    for (int i=0; i<N; ++i) {
        in[A[i]] = true;
        roots.insert(A[i]);
        for (auto it=adj[A[i]].begin(); it!=adj[A[i]].end(); ++it) {
            if (!in[*it]) continue;
            join(A[i], *it);
        }

        ans[N-i-1] = roots.size() == 1;
    }

    for (int i=0; i<N; ++i) {
        cout << (ans[i] ? "YES\n" : "NO\n");
    }
}
