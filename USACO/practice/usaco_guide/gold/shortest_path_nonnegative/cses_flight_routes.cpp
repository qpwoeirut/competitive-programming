//cses_flight_routes.cpp created at 12/19/20 20:42:26

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 100005;

int N, M, K;
multiset<pii> adj[MN];

multiset<ll> dist[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=0; i<M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace(b, c);
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, 0);
    dist[0].insert(0);
    
    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();

        if (dist[cur.se].size() >= K && *dist[cur.se].rbegin() < cur.fi) continue;
        //cerr << cur.fi << ' ' << cur.se << endl;

        for (const pii& p: adj[cur.se]) {
            if (dist[p.fi].size() < K || *dist[p.fi].rbegin() > cur.fi + p.se) {
                dist[p.fi].insert(cur.fi + p.se);
                if (dist[p.fi].size() > K) {
                    auto it = dist[p.fi].end(); --it;
                    dist[p.fi].erase(it);
                }

                pq.emplace(cur.fi + p.se, p.fi);
            }
        }
    }

    assert(dist[N-1].size() == K);
    for (auto x: dist[N-1]) {
        cout << x << ' ';
    }
    cout << endl;
}

