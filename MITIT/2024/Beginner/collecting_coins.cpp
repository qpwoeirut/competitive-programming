#include <bits/stdc++.h>

using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

struct Edge {
    int from, to;
    ll cost;
    ll reward;

    Edge(ll f, ll t, ll c, ll r): from(f), to(t), cost(c), reward(r) {}
};

const int MN = 100005;

int N, M;
vector<Edge> adj[MN];

ll best[MN];
bool proc[MN];
bool check(ll coins) {
    fill(best, best+N, -1);
    fill(proc, proc+N, false);
    priority_queue<pll> pq;
    pq.emplace(coins, 0);
    best[0] = coins;
    while (pq.size() > 0) {
        const pll p = pq.top(); pq.pop();

        if (p.second == N - 1) return true;
        proc[p.second] = true;
        if (best[p.second] > p.first) continue;

        for (const Edge& e: adj[p.second]) {
            if (best[e.to] < best[e.from] - e.cost + e.reward && best[e.from] >= e.cost) {
                if (proc[e.to]) return true;
                best[e.to] = best[e.from] - e.cost + e.reward;
                pq.emplace(best[e.to], e.to);
            }
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        ll a, b, c, r;
        cin >> a >> b >> c >> r;
        --a; --b;

        adj[a].emplace_back(a, b, c, r);
        adj[b].emplace_back(b, a, c, r);
    }

    ll lo = 0, hi = 1e16;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << '\n';
}
