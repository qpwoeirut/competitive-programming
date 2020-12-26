//cses_investigation.cpp created at 12/19/20 20:19:42

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pii;

const int MN = 100005;
const int MOD = 1e9 + 7;

struct State {
    ll dist;
    ll ways;
    int mn, mx;

    State() {
        dist = 1e18;
        ways = 0;
        mn = 1e9;
        mx = 0;
    }

    bool update(const ll _dist, const ll _ways, const int _mn, const int _mx) {
        if (dist > _dist) {
            dist = _dist;
            ways = _ways;
            mn = _mn;
            mx = _mx;
            return true;
        } else if (dist == _dist) {
            ways += _ways;
            if (ways >= MOD) ways -= MOD;
            mn = min(mn, _mn);
            mx = max(mx, _mx);
        }
        return false;
    }
};

int N, M;
multiset<pii> adj[MN];

State state[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adj[a].emplace(b, c);
    }

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.emplace(0, 0);
    state[0].update(0, 1, 0, 0);

    while (pq.size() > 0) {
        const pii cur = pq.top(); pq.pop();

        if (state[cur.se].dist < cur.fi) continue;
        for (const pii& p: adj[cur.se]) {
            if (state[p.fi].update(cur.fi + p.se, state[cur.se].ways, state[cur.se].mn + 1, state[cur.se].mx + 1)) {
                pq.emplace(state[p.fi].dist, p.fi);
            }
        }
    }

    cout << state[N-1].dist << ' ' << state[N-1].ways << ' ' << state[N-1].mn << ' ' << state[N-1].mx << endl;
}

