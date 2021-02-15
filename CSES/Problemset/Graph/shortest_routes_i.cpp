//shortest_routes_i.cpp created at 12/18/20 23:52:44

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 100005;
const ll INIT = 1e18;

int N, M;
set<pii> adj[MN];

ll dist[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        --u; --v;
        adj[u].emplace(v, c);
    }

    fill(dist, dist+N, INIT);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, 0);
    dist[0] = 0;

    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();

        if (dist[cur.se] < cur.fi) continue;

        for (const pii& p: adj[cur.se]) {
            if (dist[p.fi] > cur.fi + p.se) {
                dist[p.fi] = cur.fi + p.se;
                pq.emplace(dist[p.fi], p.fi);
            }
        }
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << dist[i];
    }
    cout << endl;
}

