#include "supertrees.h"
#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> vvi;

const int MN = 1001;
int N;

int root[MN];
int par(int u) {
    if (u == root[u]) return u;
    root[u] = par(root[u]);
    return root[u];
}
void join(int u, int v) {
    int ru = par(u), rv = par(v);
    if (ru == rv) return;
    root[ru] = rv;
}
bool dsu(const vvi& p) {
    for (int i=0; i<N; ++i) {
        root[i] = i;
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (p[i][j]) join(i, j);
        }
    }
    
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (par(i) == par(j) && p[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}
int sub2(const vvi& p) {
    if (!dsu(p)) return 0;
    vvi ans(N, vector<int>(N));
    for (int i=0; i<N; ++i) {
        if (i != par(i)) {
            ans[i][par(i)] = true;
            ans[par(i)][i] = true;
        }
        for (int j=0; j<N; ++j) assert(p[i][j] < 2);
    }
    build(ans);
    return 1;
}
int sub3(const vvi& p) {
    if (!dsu(p)) return 0;
    vvi ans(N, vector<int>(N));
    vvi groups;
    for (int i=0; i<N; ++i) {
        if (i == par(i)) {
            vector<int> cur;
            for (int j=0; j<N; ++j) {
                if (i == par(j)) {
                    cur.push_back(j);
                }
                assert(p[i][j] < 3);
            }
            groups.push_back(cur);
        }
    }
    for (int i=0; i<groups.size(); ++i) {
        int gsz = groups[i].size();
        if (gsz == 1) continue;
        if (gsz == 2) return 0;
        for (int j=0; j<gsz; ++j) {
            ans[groups[i][(j+1) % gsz]][groups[i][j]] = ans[groups[i][j]][groups[i][(j+1) % gsz]] = 1;
        }
    }

    build(ans);
    return 1;
}

int construct(std::vector<std::vector<int>> p) {
	N = p.size();

    set<int> vals;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            vals.insert(p[i][j]);
        }
    }

    if ((vals.size() == 1 && vals.count(1)) || (vals.size() == 2 && vals.count(0) && vals.count(1))) {
        return sub2(p);
    }
    if (vals.count(2)) {
        return sub3(p);
    }
    return 0;
}
