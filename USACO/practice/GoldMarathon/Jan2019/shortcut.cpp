#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 10005;
const ll INIT = 1e18;

ll N, M, T;
ll A[MN];

set<pii> adj[MN];

ll dist[MN];
int par[MN];
pii nodes[MN];

bool chmn(ll& a, const ll b) {
    if (a>b) {
        a=b;
        return true;
    }
    return false;
}

int main() {
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> T;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        --a; --b;
        adj[a].emplace(b, t);
        adj[b].emplace(a, t);
    }

    fill(dist, dist+N, INIT);
    dist[0] = 0;
    par[0] = -1;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, 0);
    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();

        if (dist[cur.SE] < cur.FI) continue;
        for (auto v: adj[cur.SE]) {
            if (chmn(dist[v.FI], cur.FI + v.SE)) {
                pq.emplace(dist[v.FI], v.FI);
                par[v.FI] = cur.SE;
            } else if (dist[v.FI] == cur.FI + v.SE && cur.SE < par[v.FI]) {
                par[v.FI] = cur.SE;
            }
        }
    }
    
    for (int i=0; i<N; ++i) {
        nodes[i] = pii(dist[i], i);
    }
    sort(nodes, nodes+N, greater<pii>());
    for (int i=0; i<N-1; ++i) {
        A[par[nodes[i].SE]] += A[nodes[i].SE];
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ans = max(ans, (dist[i] - T) * A[i]);
    }

    cout << ans << endl;
}
