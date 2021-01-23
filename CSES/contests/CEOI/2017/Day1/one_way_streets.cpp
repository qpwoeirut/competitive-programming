//one_way_streets.cpp created at 01/20/21 19:24:24

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

int component[MN];
int C = 0;
void mark_component(const int node) {
    if (component[node] != INIT) return;
    component[node] = C;
    for (const Edge& e: adj[node]) {
        if (bridge_ids.count(e.id)) continue;
        mark_component(e.v);
    }
}

void build_tree() {
    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }

    for (const int bridge_id: bridge_ids) {
        const Edge bridge = edge[bridge_id];
        Edge e(component[bridge.u], component[bridge.v], bridge.id, bridge.rev);
        adj[e.u].push_back(e);
        swap(e.u, e.v);
        e.rev ^= 1;
        adj[e.u].push_back(e);
    }
}

int anc[LG][MN];
pii range[MN];
int range_num;
void preprocess(const int node, const int par) {
    anc[0][node] = par;
    range[node].fi = range_num++;
    for (const Edge& e: adj[node]) {
        if (e.v == par) continue;
        preprocess(e.v, node);
    }
    range[node].se = range_num;
}

void init_lca() {
    fill(range, range+C, pii(-1, -1));
    range_num = 0;
    for (int i=0; i<C; ++i) {
        if (range[i].fi == -1) {
            preprocess(i, -1);
        }
    }

    for (int i=1; i<LG; ++i) {
        for (int j=0; j<C; ++j) {
            if (anc[i-1][j] == -1) {
                anc[i][j] = -1;
            } else {
                anc[i][j] = anc[i-1][anc[i-1][j]];
            }
        }
    }
}

bool is_ancestor(const int u, const int v) {
    return range[u].fi <= range[v].fi && range[v].se <= range[u].se;
}

int lca(int u, const int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i=LG-1; i>=0; --i) {
        if (anc[i][u] == -1) continue;
        if (is_ancestor(anc[i][u], v)) continue;
        u = anc[i][u];
    }
    return anc[0][u];
}

int higher(const int u, const int v) { // assume both are ancestors of a node
    if (u == INIT) return v;
    if (v == INIT) return u;
    return is_ancestor(u, v) ? u : v;
}

string ans;
int highest[MN];
int dir[MN];
bool processed[MN];
void find_directions(const int node, const int par) {
    processed[node] = true;
    for (const Edge& e: adj[node]) {
        if (e.v == par) continue;
        find_directions(e.v, node);

        if (dir[e.v] == 0) {
            continue;
        }

        if (node != highest[e.v] && higher(node, highest[e.v]) == highest[e.v]) {
            assert(dir[node] == 0 || dir[node] == dir[e.v]);
            dir[node] = dir[e.v];
            highest[node] = higher(highest[node], highest[e.v]);
        }

        bool d = dir[e.v] == -1;
        d ^= e.rev;
        ans[e.id] = d ? 'L' : 'R';
    }
}

void solve() {
    fill(disc, disc+N, INIT);
    fill(visited, visited+N, false);
    bridge_ids.clear();
    int T = 0;
    for (int i=0; i<N; ++i) {
        if (disc[i] == INIT) {
            disc[i] = 0;
            find_bridges(i, -1);
            ++T;
        }
    }

    fill(component, component+N, INIT);
    C = 0;
    for (int i=0; i<N; ++i) {
        if (component[i] == INIT) {
            mark_component(i);
            ++C;
        }
    }

    //cerr << "\n========================================\n\n";
    //cerr << "bridges: "; for (const int b: bridge_ids) { cerr << b << ' '; } cerr << endl;
    //cerr << "C=" << C << endl;
    //for (int i=0; i<N; ++i) { if (i) cerr << ' '; cerr << component[i]; } cerr << endl;
    assert(C == bridge_ids.size() + T);

    build_tree();

    fill(highest, highest+C, INIT);
    fill(dir, dir+C, 0);
    for (int i=0; i<P; ++i) {
        int x = path[i].fi;
        int y = path[i].se;
        x = component[x];
        y = component[y];

        if (x == y) continue;

        const int z = lca(x, y);
        highest[x] = higher(highest[x], z);
        highest[y] = higher(highest[y], z);
        assert(dir[x] == 0 || dir[x] == -1);
        assert(dir[y] == 0 || dir[y] == +1);
        dir[x] = -1;
        dir[y] = +1;
    }

    fill(processed, processed+C, false);
    ans = string(M, 'B');
    for (int i=0; i<C; ++i) {
        if (!processed[i]) {
            find_directions(i, -1);
        }
    }

    cout << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    //test(); return 0;

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
    for (int i=0; i<P; ++i) {
        cin >> path[i].fi >> path[i].se;
        --path[i].fi; --path[i].se;
    }
    solve();
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

4 4
4 3
4 1
2 1
1 3
0

4 3
3 2
4 3
4 3
0
*/
