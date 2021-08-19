//organigramas.cpp created at 08/14/21 13:59:18

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N;
int A[MN];
set<int> adj[MN];
vector<int> possible[MN];
 
void compress(const int u) {
    while (adj[u].size() == 1) {
        const int child = *adj[u].begin();
        A[u] += A[child];
        adj[u] = adj[child];
    }
    for (const int v: adj[u]) {
        compress(v);
    }
}

void dfs(const int u) {
    if (adj[u].empty()) {
        for (int i=0; i<=A[u]; ++i) possible[u].push_back(i);
        return;
    }
    assert(adj[u].size() == 2);

    int c1 = -1, c2 = -1;
    for (const int v: adj[u]) {
        dfs(v);
        c2 = c1;
        c1 = v;
    }

    assert(c1 != -1 && c2 != -1);

    int i = 0, j = 0;
    while (i < possible[c1].size() && j < possible[c2].size()) {
        if (possible[c1][i] < possible[c2][j]) ++i;
        else if (possible[c1][i] > possible[c2][j]) ++j;
        else {
            for (int x=0; x<=A[u]; ++x) {
                possible[u].push_back(possible[c1][i] * 2 + x);
            }
            ++i; ++j;
        }
    }
    sort(possible[u].begin(), possible[u].end());
    possible[u].resize(unique(possible[u].begin(), possible[u].end()) - possible[u].begin());
}

void solve() {
    cin >> N;
    for (int i=0; i<N; ++i) {
        A[i] = 1;
        adj[i].clear();
        possible[i].clear();
    }
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
    }

    //for (int i=0; i<N; ++i) { cerr << i << ": "; for (const int v: adj[i]) { cerr << v << ' '; } cerr << endl; }
    compress(0);
    //for (int i=0; i<N; ++i) { cerr << i << ": "; for (const int v: adj[i]) { cerr << v << ' '; } cerr << endl; }

    dfs(0);
    //for (int i=0; i<N; ++i) { cerr << i << ": "; for (const int x: possible[i]) { cerr << x << ' '; } cerr << endl; }

    cout << possible[0].back() << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) {
        solve();
    }
}

/*
4
6
0 1
0 4
1 2
1 3
4 5
5
0 1
1 2
2 3
0 4
6
0 1
1 2
2 3
3 4
0 5
4
0 1
1 2
2 3
*/
