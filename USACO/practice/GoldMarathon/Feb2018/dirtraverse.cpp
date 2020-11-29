#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;

int N;
ll name[MN];
set<int> adj[MN];

ll subans[MN], leaf_ct[MN];

ll ans;

void process(int node) {
    leaf_ct[node] = adj[node].empty();
    subans[node] = 0;
    for (const int& child: adj[node]) {
        process(child);
        leaf_ct[node] += leaf_ct[child];
        subans[node] += leaf_ct[child] * name[child] + subans[child];
    }
}

void dfs(int node, ll prev) {
    if (adj[node].empty()) return;
    ll cur = node == 0 ? subans[node] : prev - name[node] * leaf_ct[node] + (leaf_ct[0] - leaf_ct[node]) * 3;
    ans = min(ans, cur);
    for (const int& child: adj[node]) {
        dfs(child, cur);
    }
}

int main() {
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        string s;
        cin >> s;
        name[i] = s.size();        

        int M;
        cin >> M;
        if (M > 0) ++name[i];
        for (int j=0; j<M; ++j) {
            int x;
            cin >> x;
            --x;
            adj[i].insert(x);
        }
    }

    ans = 1e18;
    process(0);

    //for (int i=0; i<N; ++i) { cerr << subans[i] << ' '; } cerr << endl;
    //for (int i=0; i<N; ++i) { cerr << leaf_ct[i] << ' '; } cerr << endl;

    dfs(0, 0);

    cout << ans << endl;
}
