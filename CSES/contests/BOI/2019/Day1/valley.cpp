#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

#define FI first
#define SE second

const int MN = 100001;
const ll INIT = 1e18;

void chmn(ll& a, ll b) {if (a>b) a=b;}

struct Edge {
    ll u, v;
    ll w;
    ll idx;
    inline const bool operator<(const Edge& other) const {
        return idx < other.idx;
    }
};

ll N, S, Q, E;
bool shop[MN];
ll dist[MN], parent[MN];
pll mark[MN];
Edge edge[MN];
set<Edge> adj[MN];

bool anc(int a, int b) {
    return mark[a].FI <= mark[b].FI && mark[b].SE <= mark[a].SE;
}

struct cmps {
    inline const bool operator()(const pll& a, const pll& b) {
        return a.SE > b.SE;
    }
};

ll cmk;
void dfs(int node, int par) {
    parent[node] = par;
    mark[node].FI = cmk++;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (it->v == par) continue;
        dfs(it->v, node);
        chmn(dist[node], dist[it->v] + it->w);
    }
    if (shop[node]) {
        dist[node] = 0;
    }
    mark[node].SE = cmk;
}

bool visited[MN];
ll brute(int start, int road) {
    fill(visited, visited+N, false);
    priority_queue<pll, vector<pll>, cmps> pq;
    pq.push(pll(start, 0));

    while (pq.size() > 0) {
        pll cur = pq.top(); pq.pop();

        if (shop[cur.FI]) {
            return cur.SE;
        }

        for (auto it=adj[cur.FI].begin(); it!=adj[cur.FI].end(); ++it) {
            if (visited[it->v]) continue;
            if (it->idx == road) continue;
            visited[it->v] = true;
            pq.push(pll(it->v, cur.SE + it->w));
        }
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> S >> Q >> E;
    --E;

    for (int i=0; i<N-1; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        edge[i].idx = i;
        --edge[i].u; --edge[i].v;
        adj[edge[i].u].insert(edge[i]);
        swap(edge[i].u, edge[i].v);
        adj[edge[i].u].insert(edge[i]);
    }
    fill(shop, shop+N, false);
    for (int i=0; i<S; ++i) {
        ll s;
        cin >> s;
        --s;
        shop[s] = true;
    }

    fill(dist, dist+N, INIT);
    cmk = 0;
    dfs(E, -1);

    for (int i=0; i<Q; ++i) {
        ll road, start;
        cin >> road >> start;
        --road; --start;

        ll u = edge[road].u;
        ll v = edge[road].v;

        if (anc(u, start) && anc(v, start)) {
            ll ans = brute(start, road);        
            if (ans == -1) {
                cout << "oo\n";
            } else {
                cout << ans << '\n';
            }
        } else {
            cout << "escaped" << '\n';
        }
    }
}
/*
5 2 3 1
1 2 3
1 3 2
3 4 1
3 5 2
2
4
2 2
2 5
4 5
*/
