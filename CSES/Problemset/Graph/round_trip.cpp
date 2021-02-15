//round_trip.cpp created at 12/18/20 15:18:12

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N, M;
set<int> adj[MN];
bool V[MN];
int par[MN];

int ans = -1;
void dfs(int u, int p) {
    V[u] = true;
    par[u] = p;
    for (const int& v: adj[u]) {
        if (v == p) continue;
        if (V[v]) {
            par[v] = u;
            ans = v;
        } else {
            dfs(v, u);
        }
        if (ans != -1) return;
    }
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

    for (int i=0; i<N; ++i) {
        if (!V[i]) dfs(i, -1);
        if (ans != -1) break;
    }

    if (ans != -1) {
        vector<int> cycle;
        cycle.push_back(ans);
        int cur = par[ans];
        while (cur != ans) {
            cycle.push_back(cur);
            cur = par[cur];
        }
        cycle.push_back(ans);
        cout << cycle.size() << endl;
        for (int i=0; i<cycle.size(); ++i) {
            if (i) cout << ' ';
            cout << cycle[i] + 1;
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

