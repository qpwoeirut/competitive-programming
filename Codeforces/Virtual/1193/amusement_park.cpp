//amusement_park.cpp created at 09/20/20 08:59:19

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 20;
const ll MOD = 998244353;
int N, M;
set<int> adj[MN];

int mark[MN];
bool dfs(int node) {
    if (mark[node] == 2) return false;
    if (mark[node] == 1) return true;
    mark[node] = 1;

    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (dfs(*it)) {
            return true;
        }
    }

    mark[node] = 2;
    return false;
}

int edge[1001][2];
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;

        --u; --v;

        adj[u].insert(v);
        edge[i][0] = u;
        edge[i][1] = v;
    }

    int total = 0;
    for (int i=0; i<(1LL<<M); ++i) {
        int cur = 0;
        for (int j=0; j<M; ++j) {
            if (i & (1 << j)) {
                adj[edge[j][0]].erase(edge[j][1]);
                adj[edge[j][1]].insert(edge[j][0]);
                ++cur;
            }
        }

        bool ok = true;
        fill(mark, mark+N, 0);
        for (int j=0; j<N; ++j) {
            if (dfs(j)) {
                ok = false;
                break;
            }
        }

        if (ok) {
            total = (total + cur) % MOD;
        }

        for (int j=0; j<M; ++j) {
            if (i & (1 << j)) {
                adj[edge[j][1]].erase(edge[j][0]);
                adj[edge[j][0]].insert(edge[j][1]);
            }
        }
    }


    cout << total << endl;
}
