#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

struct Edge {
    int u, v;
    int cost;

    inline const bool operator<(const Edge& other) const {
        if (cost == other.cost) {
            if (u == other.u) {
                return v < other.v;
            }
            return u < other.u;
        }
        return cost < other.cost;
    }
};

struct Query {
    int k, v;
    int idx;

    inline const bool operator<(const Query& other) const {
        if (k == other.k) {
            if (v == other.v) {
                return idx < other.idx;
            }
            return v < other.v;
        }
        return k > other.k;
    }
};

int N, Q;
Edge edge[MN];
Query query[MN];
int ans[MN];

int par[MN], sz[MN];
int root(int u) {
    if (par[u] != u) {
        par[u] = root(par[u]);
    }
    return par[u];
}
void join(int u, int v) {
    int ru = root(u), rv = root(v);
    assert(ru != rv);

    if (sz[ru] < sz[rv]) swap(ru, rv);
    sz[ru] += sz[rv];
    par[rv] = ru;
}


int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;
    for (int i=0; i<N-1; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].cost;
        --edge[i].u;
        --edge[i].v;
    }
    sort(edge, edge+N-1);
    
    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    for (int i=0; i<Q; ++i) {
        cin >> query[i].k >> query[i].v;
        --query[i].v;
        query[i].idx = i;
    }
    sort(query, query+Q);

    int ei = N-2;
    for (int i=0; i<Q; ++i) {
        while (ei >= 0 && edge[ei].cost >= query[i].k) {
            join(edge[ei].u, edge[ei].v);
            --ei;
        }

        ans[query[i].idx] = sz[root(query[i].v)] - 1;
    }

    for (int i=0; i<Q; ++i) {
        cout << ans[i] << '\n';
    }
}
