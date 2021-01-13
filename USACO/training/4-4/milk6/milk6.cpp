/*
ID: zhongbr1
TASK: milk6
LANG: C++14
*/

//milk6.cpp created at 01/02/21 20:50:19

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

struct Edge {
    int u, v;
    int cost;
    int num;

    inline const bool operator<(const Edge& o) const {
        if (cost == o.cost) {
            if (num == o.num) {
                if (u == o.u) return v < o.v;
                return u < o.u;
            }
            return num < o.num;
        }
        return cost < o.cost;
    }
};

const int MN = 34;
const int MM = 1005;
const int INIT = 1001001001;

int N, M;
map<int,int> adj[MN];

int par[MN];
int find_path() {
    fill(par, par+N, -1);
    
    queue<pii> q;
    q.emplace(0, INIT);
    par[0] = -2;
    
    while (q.size() > 0) {
        const pii cur = q.front(); q.pop();

        if (cur.fi == N-1) return cur.se; 

        for (const pii& p: adj[cur.fi]) {
            if (p.se == 0 || par[p.fi] != -1) continue;
            par[p.fi] = cur.fi;
            q.emplace(p.fi, min(cur.se, p.se));
        }
    }

    return 0;
}

Edge edge[MM];
bool removed[MM];
int flow() {
    fill(adj, adj+N, map<int,int>());
    for (int i=0; i<M; ++i) {
        if (removed[i]) continue;
        ++adj[edge[i].u][edge[i].v];
    }

    int total = 0;
    int cur = find_path();
    while (cur > 0) {
        total += cur;

        int u = N-1;
        while (u != 0) {
            adj[par[u]][u] -= cur;
            adj[u][par[u]] += cur;
            u = par[u];
        }

        cur = find_path();
    }

    return total;
}

int main() {
    freopen("milk6.in", "r", stdin);
    freopen("milk6.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].cost;
        --edge[i].u; --edge[i].v;
        edge[i].num = i+1;
    }
    sort(edge, edge+M);

    int old_flow = flow();
    int cost = 0;
    set<int> ans;
    for (int i=0; i<M; ++i) {
        removed[i] = true;
        const int cur_flow = flow();
        if (cur_flow == old_flow) {
            removed[i] = false;
        } else {
            old_flow = cur_flow;
            cost += edge[i].cost;
            ans.insert(edge[i].num);
        }
    }

    cout << cost << ' ' << ans.size() << endl;
    for (const int x: ans) {
        cout << x << '\n';
    }
}

