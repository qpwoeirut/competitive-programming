//message_route.cpp created at 12/18/20 14:52:47

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N, M;
set<int> adj[MN];

int par[MN];

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

    fill(par, par+N, -1);
    queue<int> q;
    q.push(0);
    par[0] = -2;

    while (q.size() > 0) {
        const int u = q.front(); q.pop();
        
        for (const int& v: adj[u]) {
            if (par[v] != -1) continue;
            par[v] = u;
            q.push(v);
        }
    }

    vector<int> ans;
    int cur = N-1;
    while (-1 < par[cur]) {
        ans.push_back(cur+1);
        cur = par[cur];
    }

    if (cur != 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    ans.push_back(1);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i=0; i<ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}

