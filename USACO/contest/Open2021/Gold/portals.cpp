#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 100005 * 2;

int N;
pii A[MN];
vector<int> edge[MN];
set<int> adj[MN];

int gp[MN];

int par[MN], sz[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    sz[ru] += sz[rv];
    par[rv] = par[u] = par[v] = ru;

    return true;
}

void dfs(const int u, const int group) {
    if (gp[u] != -1) return;
    gp[u] = group;
    for (const int v: adj[u]) dfs(v, group);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].fi;
        A[i].se = i;
        for (int j=0; j<4; ++j) {
            int p;
            cin >> p;
            --p;

            edge[p].push_back(2 * i + (j >= 2));
        }
    }

    for (int i=0; i<2*N; ++i) {
        assert(edge[i].size() == 2);
        adj[edge[i][0]].insert(edge[i][1]);
        adj[edge[i][1]].insert(edge[i][0]);
    }

    fill(gp, gp+2*N, -1);
    int M = 0;
    for (int i=0; i<2*N; ++i) {
        if (gp[i] == -1) {
            dfs(i, M++);
        }
    }

    for (int i=0; i<M; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    sort(A, A+N);
    int ans = 0;
    for (int i=0; i<N; ++i) {
        if (join(gp[2 * A[i].se], gp[2 * A[i].se + 1])) ans += A[i].fi;
    }

    cout << ans << '\n';
}
