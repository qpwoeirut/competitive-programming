//building_roads.cpp created at 12/18/20 14:39:53

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;

const int MN = 100005;

int N, M;
set<int> adj[MN];

bool V[MN];
void dfs(int u) {
    if (V[u]) return;
    V[u] = true;
    for (const int& v: adj[u]) {
        dfs(v);
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

    vector<int> part;
    for (int i=0; i<N; ++i) {
        if (V[i] == false) {
            dfs(i);
            part.push_back(i+1);
        }
    }

    vector<pii> ans;
    for (int i=1; i<part.size(); ++i) {
        ans.emplace_back(part[0], part[i]);
    }

    cout << ans.size() << '\n';
    for (int i=0; i<ans.size(); ++i) {
        cout << ans[i].fi << ' ' << ans[i].se << '\n';
    }
}

