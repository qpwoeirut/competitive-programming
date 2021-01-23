//mousetrap.cpp created at 01/20/21 22:16:58

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 1000006;
const int LG = 22;
const int INIT = 1001001001;

int N, T, M;
set<int> adj[MN];

int anc[LG][MN];
pii range[MN];
int range_num;
void preprocess(const int node, const int par) {
    anc[0][node] = par;
    range[node].fi = range_num++;
    for (const int v: adj[node]) {
        if (v == par) continue;
        preprocess(v, node);
    }
    range[node].se = range_num;
}

void init_lca() {
    range_num = 0;
    preprocess(T, -1);

    for (int i=1; i<LG; ++i) {
        for (int j=0; j<N; ++j) {
            if (anc[i-1][j] == -1) {
                anc[i][j] = -1;
            } else {
                anc[i][j] = anc[i-1][anc[i-1][j]];
            }
        }
    }
}

bool is_ancestor(const int u, const int v) {
    return range[u].fi <= range[v].fi && range[v].se <= range[u].se;
}

int lca(int u, const int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i=LG-1; i>=0; --i) {
        if (anc[i][u] == -1) continue;
        if (is_ancestor(anc[i][u], v)) continue;
        u = anc[i][u];
    }
    return anc[0][u];
}

int cost[MN];
void ccost(const int u, const int par) {
    for (const int v: adj[u]) {
        if (v == par) continue;
        cost[v] = max(0, cost[u] - 1) + adj[v].size() - 1;
        ccost(v, u);
    }
}

int dist[MN];
void cdist(const int u, const int par) {
    for (const int v: adj[u]) {
        if (v == par) continue;
        dist[v] = dist[u] + 1;
        cdist(v, u);
    }
}

int dfs(const int u, const int par) {
    const int L = lca(M, u);
    if (adj[u].size() <= 1 + (L != M) || u == T) {
        //cerr << u << ' ' << L << ' ' << dist[u] << ' ' << dist[L] << ' ' << cost[u] << endl;
        const int ret = dist[u] - dist[L] + cost[u] - (L != M);
        return ret;
    }

    multiset<int,greater<int>> cur;
    for (const int v: adj[u]) {
        if (v == par) continue;
        cur.insert(dfs(v, u));
    }
    cur.erase(cur.begin());
    //cerr << u << ' ' << *cur.begin() << endl;
    return *cur.begin();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T >> M;
    --T; --M;
    for (int i=0; i<N-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    if (adj[M].size() == 1) M = *adj[M].begin();

    cost[T] = 0;
    ccost(T, -1);
    //for (int i=0; i<N; ++i) { cerr << cost[i] << ' '; } cerr << endl;
    
    dist[M] = 0;
    cdist(M, -1);
    init_lca();

    cout << dfs(M, -1) << endl;
}

/*
10 1 4
1 2
2 3
2 4
3 9
3 5
4 7
4 6
6 8
7 10

10 1 10
1 2
2 3
3 4
2 5
5 6
2 7
7 8
2 9
2 10
*/
