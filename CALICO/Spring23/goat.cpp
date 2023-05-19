#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MAXN = 100005;

int N, Q;
int P[MAXN];
ll A[MAXN];
int G[MAXN];

vector<int> adj[MAXN];
void dfs(int u, int par, vector<int>& values) {
    values.push_back(A[u]);
    for (const int v: adj[u]) {
        if (v != par) dfs(v, u, values);
    }
}

ll brute_ans[MAXN];
void brute() {
    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }
    for (int i=0; i<N; ++i) {
        if (P[i] < 0) continue;
        adj[P[i]].push_back(i);
        adj[i].push_back(P[i]);
    }
    for (int i=0; i<Q; ++i) {
        vector<int> values;
        dfs(G[i], P[G[i]], values);
        brute_ans[i] = 0;
        for (int u=0; u<values.size(); ++u) {
            for (int v=u+1; v<values.size(); ++v) {
                brute_ans[i] += gcd(values[u], values[v]);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> Q;
        for (int i=0; i<N; ++i) {
            cin >> P[i];
            --P[i];
        }
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        for (int i=0; i<Q; ++i) {
            cin >> G[i];
            --G[i];
        }
        brute();
        for (int i=0; i<Q; ++i) {
            if (i) cout << ' ';
            cout << brute_ans[i];
        }
        cout << '\n';
    }
}
