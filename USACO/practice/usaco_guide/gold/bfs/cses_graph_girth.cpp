//cses_graph_girth.cpp created at 12/19/20 19:23:15

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 2505;
const int INIT = 1001001001;

int N, M;
set<int> adj[MN];
int dist[MN];
int par[MN];

int bfs(const int start) {
    fill(par, par+N, -1);
    queue<pii> q;
    q.emplace(start, 0);
    dist[start] = 0;

    int ret = INIT;
    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();
        //cerr << "cur: " << cur.fi << ' ' << cur.se << endl;

        for (const int& v: adj[cur.fi]) {
            if (v == par[cur.fi] || v == start) continue;
            if (par[v] != -1 && par[v] != cur.fi) {
                //cerr << v << endl;
                ret = min(ret, cur.se + dist[v] + 1);
            }
            if (par[v] == -1) {
                par[v] = cur.fi;
                dist[v] = cur.se + 1;
                q.emplace(v, dist[v]);
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    int ans = INIT;
    for (int i=0; i<N; ++i) {
        const int cur = bfs(i);
        //cerr << i << ' ' << cur << endl;
        ans = min(ans, cur);
    }

    cout << (ans == INIT ? -1 : ans) << endl;
}

