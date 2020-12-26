/*
ID: zhongbr1
TASK: ditch
LANG: C++14
*/

//ditch.cpp created at 12/24/20 13:50:00

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 205;
const int INIT = 1001001001;

int N, M;
map<int,int> adj[MN];

int par[MN];
int find_path() {
    //for (int i=0; i<N; ++i) { cerr << "------ " << i << " ------\n"; for (const pii& p: adj[i]) { cerr << p.fi << ' ' << p.se << endl; } }
    fill(par, par+N, -1);
    queue<pii> q;
    par[0] = -2;
    q.emplace(0, INIT);

    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();

        if (cur.fi == N-1) {
            return cur.se;
        }

        for (const pii& p: adj[cur.fi]) {
            if (par[p.fi] != -1 || p.se == 0) continue;
            par[p.fi] = cur.fi;
            q.emplace(p.fi, min(p.se, cur.se));
        }
    }

    return 0;
}

int main() {
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> M >> N;
    for (int i=0; i<M; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        --u; --v;
        adj[u][v] += d;
    }

    int total_flow = 0;
    int cur_flow = find_path();
    while (cur_flow > 0) {
        //cerr << cur_flow << endl;
        total_flow += cur_flow;

        int node = N-1;
        while (node != 0) {
            adj[par[node]][node] -= cur_flow;
            adj[node][par[node]] += cur_flow;

            node = par[node];
        }
        cur_flow = find_path();
    }

    cout << total_flow << endl;
}
