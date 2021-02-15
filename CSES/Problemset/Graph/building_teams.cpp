//building_teams.cpp created at 12/18/20 15:08:16

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, M;
set<int> adj[MN];

bool ok;
int mark[MN];
void dfs(int u, bool x) {
    if (mark[u] != -1) {
        if (mark[u] != x) ok = false;
        return;
    }
    mark[u] = x;
    for (const int& v: adj[u]) {
        dfs(v, !x);
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

    ok = true;
    fill(mark, mark+N, -1);
    for (int i=0; i<N; ++i) {
        if (mark[i] == -1) {
            dfs(i, 0);
        }
    }

    if (!ok) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << mark[i] + 1;
    }
    cout << endl;
}

