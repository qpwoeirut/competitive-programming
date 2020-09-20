#include "supertrees.h"
#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;

const int MN = 1001;
int N;

int root[MN];
int oroot[MN];
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
int opar(int u) {
    if (u == oroot[u]) return u;
    oroot[u] = opar(oroot[u]);
    return oroot[u];
}
void ojoin(int u, int v) {
    int ru = opar(u), rv = opar(v);
    if (ru == rv) return;
    oroot[ru] = rv;
}
bool dsu(const vvi& p) {
    for (int i=0; i<N; ++i) {
        root[i] = i;
        oroot[i] = i;
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (p[i][j] == 3) return 0;
            if (p[i][j]) join(i, j);
            if (p[i][j] == 1) ojoin(i, j);
        }
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (p[i][j] == 0 && par(i) == par(j)) return 0;
            if (p[opar(i)][j] != p[i][j]) return 0;
        }
    }
    
    return 1;
}

int ones[MN];
vvi ans;
bool make_part(const vvi& p, const vector<int>& nodes) {
    set<pii, greater<pii>> q;
    for (int i=0; i<nodes.size(); ++i) {
        q.insert(pii(ones[nodes[i]], nodes[i]));
    }

    int root = -1;
    int last = -1;

    int inner_ct = 0;
    while (q.size() > 0) {
        int cur = q.begin()->second;
        q.erase(q.begin());
        ++inner_ct;

        if (root == -1) {
            root = cur;
        }
        if (last != -1) {
            ans[cur][last] = 1;
            ans[last][cur] = 1;
        }
        last = cur;

        for (int i=0; i<N; ++i) {
            if (cur == i) continue;
            if (p[cur][i] == 1) {
                ans[cur][i] = 1;
                ans[i][cur] = 1;
                q.erase(pii(ones[i], i));
            }
        }
    }
    assert(root != -1 && last != -1);
    if (inner_ct <= 2) {
        for (int i=0; i<N; ++i ) {
            if (p[root][i] == 2 || p[last][i] == 2) {
                return false;
            }
        }
    }

    if (root != last) {
        ans[root][last] = 1;
        ans[last][root] = 1;
    }
    return 1;
}

int construct(std::vector<std::vector<int>> p) {
	N = p.size();
    if (!dsu(p)) return 0;

    map<int, vector<int>> parts;
    for (int i=0; i<N; ++i) {
        parts[par(i)].push_back(i);
        for (int j=0; j<N; ++j) {
            if (p[i][j] == 1) ++ones[i];
        }
    }

    ans = vvi(N, vector<int>(N));
    for (auto it=parts.begin(); it!=parts.end(); ++it) {
        if (!make_part(p, it->second)) return 0;
    }

    build(ans);

    return 1;
}
