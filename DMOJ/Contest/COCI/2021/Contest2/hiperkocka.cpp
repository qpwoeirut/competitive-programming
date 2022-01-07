//hiperkocka.cpp created at 12/23/21 19:28:44

#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

#define clock high_resolution_clock

const int MN = 20;
const int MXN = (1 << 17) + 5;

int N;
set<int> adj[MXN];
set<int> tree[MN];
set<int> removed[MXN];

vector<vector<int>> ans;

mt19937 rng(8);

bool dfs(const int tu, const int tpar, const int u, const int par) {
    if ((int)adj[u].size() - (int)removed[u].size() < tree[tu].size()) return false;
    ans.back()[tu] = u;
    auto it = adj[u].begin();
    for (const int tv: tree[tu]) {
        if (tv == tpar) continue;
        while (*it == par || removed[u].count(*it)) assert(++it != adj[u].end());
        removed[u].insert(*it);
        if (!dfs(tv, tu, *it, u)) return false;
        ++it;
    }
    return true;
}

void remove_edges(const int tu, const int tpar) {
    for (const int tv: tree[tu]) {
        if (tv == tpar) continue;
        adj[ans.back()[tu]].erase(ans.back()[tv]);
        adj[ans.back()[tv]].erase(ans.back()[tu]);
        remove_edges(tv, tu);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        int x, y;
        cin >> x >> y;
        tree[x].insert(y);
        tree[y].insert(x);
    }
    const clock::time_point start = clock::now();

    for (int i=0; i<(1 << N); ++i) {
        for (int j=0; j<N; ++j) {
            adj[i].insert((1 << j) ^ i);
        }
    }

    while (duration_cast<duration<double>>(clock::now() - start).count() < 0.98) {
        ans.push_back(vector<int>(N + 1));
        const int start = rng() % (1 << N);
        assert(0 <= start && start < (1 << N));
        if (dfs(0, -1, start, -1)) {
            remove_edges(0, -1);
            for (const int u: ans.back()) {
                removed[u].clear();
            }
        } else {
            ans.pop_back();
        }
    }

    cout << ans.size() << '\n';
    for (const vector<int>& v: ans) {
        for (int i=0; i<v.size(); ++i) {
            if (i) cout << ' ';
            cout << v[i];
        }
        cout << '\n';
    }
}

