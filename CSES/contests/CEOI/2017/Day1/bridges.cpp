//bridges.cpp created at 01/20/21 20:37:45

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
    int ret = disc[node];
    for (const Edge& e: adj[node]) {
        if (e.id == edge_id) continue;
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

void flood(const int node, bool V[], const int edge) {
    if (V[node]) return;
    V[node] = true;
    for (const Edge& e: adj[node]) {
        if (e.id == edge) continue;
        flood(e.v, V, edge);
    }
}
bool V1[MN];
bool V2[MN];
set<int> bruted;
void brute_bridges() {
    for (int i=0; i<N; ++i) {
        for (const Edge& e: adj[i]) {
            fill(V1, V1+N, false);
            fill(V2, V2+N, false);

            flood(e.u, V1, -1);
            flood(e.u, V2, e.id);
            for (int j=0; j<N; ++j) {
                if (V1[j] != V2[j]) {
                    bruted.insert(e.id);
                    break;
                }
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (N=3; N<=10; ++N) {
        cerr << "N=" << N << endl;
        for (M=N-1; M<(N*(N-1)) >> 1; ++M) {
            for (int t=0; t<100000; ++t) {
                for (int i=0; i<N; ++i) {
                    adj[i].clear();
                }
                for (int i=0; i<M; ++i) {
                    edge[i].u = (rand() % N) + 1;
                    edge[i].v = (rand() % N) + 1;
                    if (edge[i].u == edge[i].v) continue;

                    --edge[i].u; --edge[i].v;
                    edge[i].id = i;
                    edge[i].rev = false;

                    adj[edge[i].u].push_back(edge[i]);
                    swap(edge[i].u, edge[i].v);
                    edge[i].rev ^= 1;
                    adj[edge[i].u].push_back(edge[i]);
                    swap(edge[i].u, edge[i].v);
                    edge[i].rev ^= 1;
                }
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
                
                bruted.clear();
                brute_bridges();
                if (bruted != bridge_ids) {
                    cout << N << ' ' << M << endl;

                    for (int i=0; i<M; ++i) {
                        cout << edge[i].u + 1 << ' ' << edge[i].v + 1 << endl;
                    }
                    cout << endl;
                    for (const int x: bruted) { cout << x << ' '; } cout << endl;
                    for (const int x: bridge_ids) { cout << x << ' '; } cout << endl;
                    assert(0);
                }
            }
        }
    }


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

