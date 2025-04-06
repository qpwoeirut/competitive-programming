#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

#define fi first
#define se second

const int MN = 100005;

int N, M;
vector<pii> fadj[MN], radj[MN];

int f_req[MN], r_req[MN];

void ff(const vector<pii> adj[MN], int req[MN]) {
    fill(req, req+N, 1e9 + 5);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    req[0] = 0;
    pq.emplace(0, 0);
    while (pq.size() > 0) {
        const pii p = pq.top(); pq.pop();
        if (p.fi > req[p.se]) continue;

        for (const pii& e: adj[p.se]) {
            if (req[e.fi] > max(p.fi, e.se)) {
                req[e.fi] = max(p.fi, e.se);
                pq.emplace(req[e.fi], e.fi);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    for (int i=0; i<M; ++i) {
        int u, v, c;
        cin >> u >> v >> c; --u; --v;
        fadj[u].emplace_back(v, c);
        radj[v].emplace_back(u, c);
    }
    ff(fadj, f_req);
    ff(radj, r_req);

    for (int i=0; i<N; ++i) {
        if (f_req[i] < r_req[i]) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
}
