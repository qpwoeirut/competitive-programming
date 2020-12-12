#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
vector<int> adj[MN];

int K;
int dfs(const int u, const int par) {
    if (adj[u].size() == 1 && par == adj[u][0]) {
        return 0;
    } else if (adj[u].size() == 2 && (par == adj[u][0] || par == adj[u][1])) {
        const int len = (par == adj[u][0] ? dfs(adj[u][1], u) : dfs(adj[u][0], u)) + 1;
        return len == K ? 0 : (len == 0 ? -1 : len);
    }
    multiset<int> paths;
    for (const int& v: adj[u]) {
        if (v == par) continue;
        const int len = dfs(v, u) + 1;
        if (len == K) continue;
        else if (len == 0) {
            //cerr << K << ' ' << u << ' ' << par << ' ' << -1 << endl;
            return -1;
        }

        const auto it = paths.find(K - len);
        if (it == paths.end()) {
            paths.insert(len);
        } else {
            paths.erase(it);
        }
    }

    if (paths.size() > 1) {
        //cerr << K << ' ' << u << ' ' << par << ' ' << -1 << endl;
        return -1;
    }
    if (paths.empty()) {
        //cerr << K << ' ' << u << ' ' << par << ' ' << 0 << endl;
        return 0;
    }
    //cerr << K << ' ' << u << ' ' << par << ' ' << *paths.begin() << endl;
    return *paths.begin();
}

int main() {
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    string ans(N-1, '0');
    ans[0] = '1';
    for (K=N-1; K>0; --K) {
        if (ans[K-1] == '1') continue;

        if (((N-1) % K) == 0 && dfs(0, -1) == 0) {
            ans[K-1] = '1';

            for (int x=2; x*x<=K; ++x) {
                if ((K % x) == 0) {
                    ans[(K / x) - 1] = '1';
                    ans[x - 1] = '1';
                }
            }
        }
    }
    cout << ans << endl;
}
