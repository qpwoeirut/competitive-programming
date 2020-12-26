//high_score.cpp created at 12/19/20 00:08:03

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 2505;
const int MM = 5005;
const ll INIT = 1e18;

struct Edge {
    int u, v;
    ll d;
};

int N, M;
Edge edge[MM];

ll dist[MN];
bool valid[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].d;
        --edge[i].u; --edge[i].v;
    }

    fill(dist+1, dist+N, -INIT);
    valid[N-1] = true;

    for (int i=0; i<N-1; ++i) {
        for (int j=0; j<M; ++j) {
            if (dist[edge[j].u] == -INIT) continue;
            dist[edge[j].v] = max(dist[edge[j].v], dist[edge[j].u] + edge[j].d);
            valid[edge[j].u] |= valid[edge[j].v];
        }
    }
    for (int j=0; j<M; ++j) {
        if (dist[edge[j].u] == -INIT) continue;
        if (dist[edge[j].v] < dist[edge[j].u] + edge[j].d && valid[edge[j].v]) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << dist[N-1] << endl;
}

