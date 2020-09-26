#include "stations.h"
#include <bits/stdc++.h>

using namespace std;

const int MN = 1001;

set<int> adj[MN];
vector<int> lbl;

int cur;
void dfs(int node, int par, bool pre) {
    if (pre) lbl[node] = cur++;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        dfs(*it, node, !pre);
    }
    if (!pre) lbl[node] = cur++;
}

std::vector<int> label(int n, int k, std::vector<int> u, std::vector<int> v) {
    for (int i=0; i<n; ++i) {
        adj[i].clear();
    }
    assert(u.size() == v.size());
    for (int i=0; i<u.size(); ++i) {
        adj[u[i]].insert(v[i]);
        adj[v[i]].insert(u[i]);
    }

    lbl = vector<int>(n);
    cur = 0;
    dfs(0, -1, true);
    //cerr << "lbl: "; for (int i=0; i<lbl.size(); ++i) { cerr << lbl[i] << ' ' ; } cerr << endl;
    return lbl;
}

int find_next_station(int s, int t, std::vector<int> c) {
    //cerr << "s,t,c: " << s << ' ' << t << ", "; for (int i=0; i<c.size(); ++i) cerr << c[i] << ' '; cerr << endl;
    assert(!c.empty());
    if (c.size() == 1) {
        return c[0];
    }
    if (s < c[0]) { // preorder
        if (s > t || t > c[c.size() - 2]) {
           return c.back();
        } else {
           return *lower_bound(c.begin(), c.end(), t);
        }
    } else if (s > c.back()) { // postorder
        if (s < t || t < c[1]) {
            return c[0];
        } else {
            int idx = upper_bound(c.begin(), c.end(), t) - c.begin();
            assert(idx > 0);
            return c[idx - 1];
        } 
    } else assert(false);
}
/*
1
5 10
0 1
1 2
1 3
2 4
2
2 0 1
1 3 3
*/
