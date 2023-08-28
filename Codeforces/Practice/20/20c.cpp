//20c.cpp created at 09/09/20 20:40:21

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MN = 100001;

ll N, M;
vector<pll> adj[MN];
ll dist[MN];
set<pll> q;
ll par[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    for (int i=0; i<M; i++) {
        ll a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj[a].push_back(pll(b, w));
        adj[b].push_back(pll(a, w));
    }

    fill(dist, dist+N, 1e18);
    fill(par, par+N, -1);
    dist[0] = 0;

    q.insert(pll(dist[0], 0));

    while (q.size() > 0) {
        pll cur = *q.begin();
        q.erase(q.begin());

        if (cur.second == N-1) {
            break;
        }

        for (int i=0; i<adj[cur.second].size(); i++) {
            if (dist[adj[cur.second][i].first] > dist[cur.second] + adj[cur.second][i].second) {
                q.erase(pll(dist[adj[cur.second][i].first], adj[cur.second][i].first));
                dist[adj[cur.second][i].first] = dist[cur.second] + adj[cur.second][i].second;
                q.insert(pll(dist[adj[cur.second][i].first], adj[cur.second][i].first));
                par[adj[cur.second][i].first] = cur.second;
            }
        }
        //done[cur.second] = true;
    }

    ll node = N-1;
    vector<ll> path;
    while (node != -1) {
        path.push_back(node);
        node = par[node];
    }
    reverse(path.begin(), path.end());
    if (path.size() == 1) {
        cout << -1 << endl;
    } else {
        for (int i=0; i<path.size(); i++) {
            if (i) cout << ' ';
            cout << path[i] + 1;
        }
        cout << endl;
    }
}
