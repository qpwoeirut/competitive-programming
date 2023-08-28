//spring_cleaning.cpp created at 09/10/20 21:51:31

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

typedef long long ll;

const ll MN = 2 * 100001;

ll N, Q, D;
set<ll> adj[MN];
ll inc[MN];
ll cost[MN];
void dfs(ll node, ll par) {
    debug(node);
    if (adj[node].size() == 1) {
        inc[node] = 1;
        cost[node] = 0;
        return;
    }
    inc[node] = 0;
    cost[node] = 0;
    for (set<ll>::iterator it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        dfs(*it, node);

        inc[node] += inc[*it];
        if (inc[node] > 2) inc[node] -= 2;
        cost[node] += cost[*it] + inc[*it];
    }
}

int main() {
    cin >> N >> Q;

    for (int i=0; i<N-1; ++i) {
        ll u, v;
        cin >> u >> v;
        --u; --v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    ll root = 0;
    for (root=0; root<N; ++root) {
        if (adj[root].size() > 1) break;
    }

    for (int i=0; i<Q; i++) {
        cin >> D;

        for (int j=0; j<D; ++j) {
            ll a;
            cin >> a;
            --a;

            adj[a].insert(N + j);
            adj[N+j].insert(a);
        }

        dfs(root, -1);
        debug(root);
        debug1(inc, N+D);
        debug1(cost, N+D);

        if (inc[root] == 1) {
            cout << -1 << endl;
        } else {
            cout << cost[root] << endl;
        }

        for (int j=0; j<N; ++j) {
            for (set<ll>::iterator it=adj[j].begin(); it!=adj[j].end();) {
                if (*it >= N) {
                    it = adj[j].erase(it);
                } else ++it;
            }
        }
        for (int j=N; j<N+D; ++j) {
            adj[j] = set<ll>();
        }
    }
}
