#include <bits/stdc++.h>

using namespace std;

const int MN = 1003;

int A[MN];
int par[MN];
bool leaf[MN];

template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
            jmp.emplace_back(V.size() - pw * 2 + 1);
            for (int j=0; j<jmp[k].size(); ++j) {
                jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b - a);
        return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};

struct LCA {
    int T = 0;
    vector<int> time, path, ret;
    RMQ<int> rmq;

    LCA(vector<vector<int>>& C) : time(C.size()), rmq((dfs(C, 0, -1), ret)) {}
    void dfs(vector<vector<int>>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};


int cost[MN];
void dfs_cost(const vector<vector<int>>& child, int u) {
    cost[u] += A[u];
    for (int v: child[u]) {
        cost[v] = cost[u];
        dfs_cost(child, v);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M;
    cin >> N >> M;

    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }
    ++N;

    vector<vector<int>> child(N, vector<int>());
    fill(par, par+N, 0);
    fill(leaf, leaf+N, true);
    for (int i=0; i<M; ++i) {
        int a, b;
        cin >> a >> b;
        child[a].push_back(b);
        par[b] = a;
        leaf[a] = false;
    }
    leaf[0] = false;
    for (int i=1; i<N; ++i) {
        if (par[i] == 0) child[0].push_back(i);
    }

    A[0] = 0;
    cost[0] = 0;
    dfs_cost(child, 0);

    LCA lca(child);
    int ans = 1e9;
    for (int i=1; i<N; ++i) {
        if (!leaf[i]) continue;
        for (int j=i+1; j<N; ++j) {
            if (!leaf[j]) continue;
            int L = lca.lca(i, j);

            ans = min(ans, cost[i] + cost[j] - cost[L]);
        }
    }

    cout << ans << '\n';
}
/*
5 1
1 2 4 8 16
2 3
*/
