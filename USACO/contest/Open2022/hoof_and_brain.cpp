#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

#define fi first
#define se second

const int MN = 5003;

int N, M;
vector<int> adj[MN], radj[MN];
int Q;

pii dp[MN][MN];  // winning moves for hoof
bool queued[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    queue<pii> q;

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            dp[i][j] = (i == j ? pii(0, 0) : pii(adj[i].size(), adj[j].size()));
        }
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (dp[i][j].fi == 0 || dp[i][j].se == 0) {
                q.emplace(i, j);
                queued[i][j] = true;
            }
        }
    }

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();
        const int u = cur.fi, v = cur.se;

        for (const int w: radj[u]) {
            if (!queued[w][v] && --dp[w][v].fi == 0) {
                queued[w][v] = true;
                q.emplace(w, v);
            }
        }
        for (const int w: radj[v]) {
            if (!queued[u][w] && --dp[u][w].se == 0) {
                queued[u][w] = true;
                q.emplace(u, w);
            }
        }
    }

    //for (int i=0; i<N; ++i) { for (int j=0; j<N; ++j) {
    //    cerr << queued[i][j] << ' ' << dp[i][j].fi << ' ' << dp[i][j].se << " , "; } cerr << endl; }

    cin >> Q;
    string ans(Q, '?');
    for (int i=0; i<Q; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        ans[i] = queued[x][y] ? 'B' : 'H';
    }

    cout << ans << '\n';
}

