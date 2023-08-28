//magic_tree.cpp created at 09/20/20 12:11:28

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;

struct Fruit {
    int node, day;
    ll val;
    Fruit() {
        node = -1;
        day = -1;
        val = 0;
    }
    Fruit(int a, int b, int c) {
        node = a;
        day = b;
        val = c;
    }
};

const int MN = 100001;

int N, M, K;
set<int> adj[MN];
Fruit fruit[MN];

ll dp[MN][1001];

ll dfs(int node, int t) {
    if (dp[node][t] != -1) {
        return dp[node][t];
    }
    dp[node][t] = 0;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        dp[node][t] += dfs(*it, t);
    }
    if (fruit[node].day == t) {
        dp[node][t] += fruit[node].val;
    }
    dp[node][t] = max(dp[node][t], dp[node][t-1]);
    return dp[node][t];
}


void solve() {
    for (int i=0; i<N; ++i) {
        for (int j=1; j<=K; ++j) {
            dp[i][j] = -1;
        }
    }
    for (int i=1; i<=K; ++i) {
        dfs(0, i);
    }
    cout << dp[0][K] << endl;
}

vector<int> order;
void dfs3(int node) {
    if (fruit[node].node == node) {
        assert(fruit[node].val == 1);
        order.push_back(fruit[node].day);
    }
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        dfs3(*it);
    }
}
void solve_sub3() {
    order.clear();
    dfs3(0);

    int ans = 1;
    map<int,int, greater<int>> mem;
    for (int i=0; i<order.size(); ++i) {
        auto it = mem.upper_bound(order[i]);
        if (it == mem.begin()) {
            mem[order[i]] = 1;
        } else {
            --it;
            int cur = it->SE + 1;
            for (++it; it!=mem.end();) {
                if (it->SE < cur) {
                    it = mem.erase(it);
                } else ++it;
            }
            mem[order[i]] = cur; 
            ans = max(ans, cur);
        }
    }
    cout << ans << endl;
}

int days[MN];
int main() {
    cin >> N >> M >> K;
    for (int i=1; i<N; ++i) {
        int u;
        cin >> u;
        --u;

        adj[u].insert(i);
    }

    ll sub2 = 0;
    for (int i=0; i<M; ++i) {
        int v, d, w;
        cin >> v >> d >> w;
        --v;
        fruit[v] = Fruit(v, d, w);
        sub2 += w;
        days[i] = d;
    }
    sort(days, days+M);
    K = unique(days, days+M) - days;

    int mx_adj = 0;
    ll mx_w = 0;
    for (int i=0; i<N; ++i) {
        if (fruit[i].day > 0) {
            fruit[i].day = lower_bound(days, days+K, fruit[i].day) - days;
            ++fruit[i].day;
            mx_w = max(mx_w, fruit[i].val);
        }
        mx_adj = max(mx_adj, (int)adj[i].size());
    }
    ++K;
    assert(K <= M);

    if (K > 1000) {
        if (mx_adj == 1 && mx_w == 1) {
            solve_sub3();
        } else {
            cout << sub2 << endl;
        }
    } else {
        solve();
    }
}
