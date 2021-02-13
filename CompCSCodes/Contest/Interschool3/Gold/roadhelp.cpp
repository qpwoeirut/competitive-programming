//roadhelp.cpp created at 02/07/21 13:26:54
// AC with 38:17 remaining
// 2:25pm
// AKed CompCS Gold
// also last 40 mins were done during A-Star class :flushed:

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

struct Edge {
    int u, v;
    ll w;
    int idx;

    Edge(const int _u, const int _v, const ll _w, const int _idx) {
        u = _u;
        v = _v;
        w = _w;
        idx = _idx;
    }

    inline const bool operator<(const Edge& o) const {
        return idx < o.idx;
    }
};

bool chmn(ll& a, const ll b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

const int MN = 1003;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

int N, M;
set<Edge> adj[MN];

ll dist[MN];
ll ways[MN];
vector<pii> prv[MN];
ll ans[MN << 1];
ll mult[MN];

void dijkstra(const int start) {
    fill(dist, dist+N, INF);
    fill(ways, ways+N, 0);
    fill(prv, prv+N, vector<pii>());

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, start);
    dist[start] = 0;
    ways[start] = 1;

    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();
        //cerr << cur.fi << ' ' << cur.se << endl;

        if (dist[cur.se] < cur.fi) continue;

        for (const Edge& e: adj[cur.se]) {
            if (chmn(dist[e.v], dist[e.u] + e.w)) {
                prv[e.v].clear();
                ways[e.v] = 0;
                pq.emplace(dist[e.v], e.v);
            }
            if (dist[e.v] == dist[e.u] + e.w) {
                prv[e.v].emplace_back(e.u, e.idx);
                ways[e.v] += ways[e.u];
                if (ways[e.v] >= MOD) ways[e.v] -= MOD;
            }
        }
    }

    priority_queue<pii> pq2;
    for (int i=0; i<N; ++i) {
        pq2.emplace(dist[i], i);
        mult[i] = 1;
    }

    while (pq2.size() > 0) {
        const pii cur = pq2.top(); pq2.pop();

        for (const pii& p: prv[cur.se]) {
            ans[p.se] = (ans[p.se] + ways[p.fi] * mult[cur.se]) % MOD;
            mult[p.fi] += mult[cur.se];
        }
    }

    //for (int i=0; i<N; ++i) { cerr << i; for (const pii p: prv[i]) { cerr << " (" << p.fi << ' ' << p.se << ')'; } cerr << endl; }
    //cerr << "dist:"; for (int i=0; i<N; ++i) { cerr << ' ' << dist[i]; } cerr << endl;
    //cerr << "ways:"; for (int i=0; i<N; ++i) { cerr << ' ' << ways[i]; } cerr << endl;
    //cerr << "mult:"; for (int i=0; i<N; ++i) { cerr << ' ' << mult[i]; } cerr << endl;
    //cerr << "ans:"; for (int i=0; i<M; ++i) { cerr << ' ' << ans[i]; } cerr << endl;
    //cerr << endl;
}

int main() {
    freopen("roadhelp.in", "r", stdin);
    freopen("roadhelp.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].emplace(u, v, w, i);
        adj[v].emplace(v, u, w, i);
    }

    fill(ans, ans+M, 0);
    for (int i=0; i<N; ++i) {
        dijkstra(i);
    }

    for (int i=0; i<M; ++i) {
        cout << ans[i] << '\n';
    }
}

