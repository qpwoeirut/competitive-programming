//asdf.cpp created at 01/20/21 22:55:55

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

struct Edge {
    int u, v;
    int id;
    bool rev;

    Edge() {
        u = v = id = -1;
        rev = false;
    }
    Edge(const int _u, const int _v, const int _id, const int _rev) {
        u = _u;
        v = _v;
        id = _id;
        rev = _rev;
    }
};

const int MN = 100005;
const int LG = 20;
const int INIT = 1001001001;

int N, M, P;
Edge edge[MN];
pii path[MN];
vector<Edge> adj[MN];

int disc[MN];
bool visited[MN];
set<int> bridge_ids;
int find_bridges(const int node, const int edge_id) {
    if (visited[node]) return INIT;
    //cerr << node << ' ' << edge_id << endl;
    int ret = disc[node];
    for (const Edge& e: adj[node]) {
        if (e.id == edge_id) continue;
        //cerr << "e.id,e.v,disc[v]: " << e.id << ' ' << e.v << ' ' << disc[e.v] << endl;
        if (disc[e.v] < disc[e.u]) {
            ret = min(ret, disc[e.v]);
        } else {
            disc[e.v] = disc[node] + 1;
            ret = min(ret, find_bridges(e.v, e.id));
        }
    }

    if (ret == disc[node] && edge_id != -1) {
        bridge_ids.insert(edge_id);
    }

    visited[node] = true;
    return ret;
}

int prv[MN], used[MN];
char dir[MN];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v;
        --edge[i].u; --edge[i].v;
        edge[i].id = i;
        edge[i].rev = false;
        if (edge[i].u == edge[i].v) continue;

        adj[edge[i].u].push_back(edge[i]);
        swap(edge[i].u, edge[i].v);
        edge[i].rev ^= 1;
        adj[edge[i].u].push_back(edge[i]);
        swap(edge[i].u, edge[i].v);
        edge[i].rev ^= 1;
    }
    cin >> P;
    set<pii> pairs;
    for (int i=0; i<P; ++i) {
        cin >> path[i].fi >> path[i].se;
        --path[i].fi; --path[i].se;
        pairs.insert(path[i]);
    }
    
    fill(disc, disc+N, INIT);
    fill(visited, visited+N, false);
    bridge_ids.clear();
    for (int i=0; i<N; ++i) {
        if (disc[i] == INIT) {
            disc[i] = 0;
            find_bridges(i, -1);
        }
    }

    string ans(M, 'B');
    for (const pii& p: pairs) {
        //cerr << p.fi << ' ' << p.se << endl;
        fill(prv, prv+N, -1);
        fill(used, used+N, -1);
        prv[p.fi] = -2;
        queue<int> q;
        q.push(p.fi);
        while (q.size() > 0) {
            const int u = q.front(); q.pop();

            if (u == p.se) break;

            for (const Edge& e: adj[u]) {
                if (prv[e.v] == -1) {
                    prv[e.v] = u;
                    used[e.v] = e.id;
                    dir[e.v] = e.rev ? 'L' : 'R';
                    q.push(e.v);
                }
            }
        }

        int cur = p.se;
        while (prv[cur] != -2) {
            if (bridge_ids.count(used[cur])) {
                ans[used[cur]] = dir[cur];
            }
            cur = prv[cur];
        }
    }

    cout << ans << endl;
}
/*
5 6
1 2
1 2
4 3
2 3
1 3
5 1
2
4 5
1 3
*/
