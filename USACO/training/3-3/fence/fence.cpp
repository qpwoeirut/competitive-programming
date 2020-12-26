/*
ID: zhongbr1
TASK: fence
LANG: C++14
*/

//fence.cpp created at 12/22/20 16:47:49

#include <bits/stdc++.h>

using namespace std;

const int MN = 505;

int M;
multiset<int> adj[MN];

vector<int> path;

void find_path(const int u) {
    while (adj[u].size() > 0) {
        const int v = *adj[u].begin();
        adj[u].erase(adj[u].begin());
        adj[v].erase(adj[v].find(u));

        find_path(v);
    }
    path.push_back(u);
}

int main() {
    freopen("fence.in", "r", stdin);
    freopen("fence.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    for (int i=0; i<500; ++i) {
        if (adj[i].size() & 1) {
            find_path(i);
            break;
        }
    }

    if (path.empty()) {
        for (int i=0; i<500; ++i) {
            if (adj[i].size() > 0) {
                find_path(i);
                break;
            }
        }
    }
    reverse(path.begin(), path.end());

    for (const int x: path) {
        cout << x+1 << '\n';
    }
}

