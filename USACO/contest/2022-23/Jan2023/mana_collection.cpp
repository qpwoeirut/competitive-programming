#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pii=pair<int,int>;

const int MN = 10;
const int MASK = 1 << MN;
const ll INF = 1e12;

int N, M, Q;
int A[MN];
ll adj[MN][MN];

vector<pii> paths[MN][MASK];

void rec(int src, int cur, int mask, ll time, ll mana_lost) {
    for (int u=0; u<N; ++u) {
        if (mask & (1 << u)) continue;
        if (adj[u][cur] == INF) continue;
        rec(src, u, mask ^ (1 << u), time + adj[u][cur], mana_lost + (time + adj[u][cur]) * A[u]);
    }

    paths[src][mask].emplace_back(time, mana_lost);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int u=0; u<N; ++u) {
        for (int v=0; v<N; ++v) {
            adj[u][v] = INF;
        }
    }
    for (int i=0; i<M; ++i) {
        int a, b, t;
        cin >> a >> b >> t; --a; --b;
        adj[a][b] = t;
    }
    for (int u=0; u<N; ++u) {
        rec(u, u, 1 << u, 0, 0);
    }

    cin >> Q;
    for (int q=0; q<Q; ++q) {
        ll s, e;
        cin >> s >> e; --e;
        ll ans = 0;
        for (int m=0; m<MASK; ++m) {
            ll round = 0;
            for (int u=0; u<N; ++u) {
                if (m & (1 << u)) {
                    round += A[u];
                }
            }
            for (int i=0; i<paths[e][m].size(); ++i) {
                if (paths[e][m][i].first <= s) {
                    ans = max(ans, round * s - paths[e][m][i].second);
                }
            }
        }

        cout << ans << '\n';
    }
}
