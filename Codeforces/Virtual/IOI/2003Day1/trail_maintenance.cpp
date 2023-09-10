//trail_maintenance.cpp created at 09/09/23 18:48:22

#include <bits/stdc++.h>

using namespace std;

const int MN = 200;
const int MM = 6000;

struct Edge {
    int a, b, dist;
};

int N, W;
Edge edges[MM];

int csz[MN], par[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(int u, int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;
    if (csz[ru] < csz[rv]) {
        swap(ru, rv);
        swap(u, v);
    }

    csz[ru] += csz[rv];
    par[v] = par[rv] = par[ru];
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> W;
    for (int w=0; w<W; ++w) {
        cin >> edges[w].a >> edges[w].b >> edges[w].dist; --edges[w].a; --edges[w].b;

        for (int i=w; i>0; --i) {
            if (edges[i - 1].dist > edges[i].dist) {
                swap(edges[i - 1], edges[i]);
            }
        }

        for (int u=0; u<N; ++u) {
            csz[u] = 1;
            par[u] = u;
        }

        int ans = 0;
        for (int i=0; i<=w; ++i) {
            if (join(edges[i].a, edges[i].b)) {
                ans += edges[i].dist;
            }
            //cerr << edges[i].dist << ' ' << ans << endl;
        }
        if (csz[root(0)] < N) ans = -1;
        cout << ans << '\n';
        cout.flush();
    }
}

