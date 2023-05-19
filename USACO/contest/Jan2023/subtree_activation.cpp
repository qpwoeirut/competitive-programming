#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N;
vector<int> child[MN];
int depth[MN];

// path[u] -> # of nodes in longest path rooted at u
// leaf[u] -> # of nodes in longest path from u to leaf
int path[MN], leaf[MN];

void dfs(const int u) {
    leaf[u] = 1;
    int mx1 = 0, mx2 = 0;
    for (int c: child[u]) {
        depth[c] = depth[u] + 1;
        dfs(c);
        leaf[u] = max(leaf[u], leaf[c] + 1);

        mx2 = max(mx2, leaf[c]);
        if (mx1 < mx2) swap(mx1, mx2);
    }
    path[u] = mx1 + mx2 + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=1; i<N; ++i) {
        int par;
        cin >> par; --par;
        child[par].push_back(i);
    }

    depth[0] = 0;
    dfs(0);

    int longest_path = 0;
    for (int i=0; i<N; ++i) {
        longest_path = max(longest_path, path[i] + depth[i]);
    }

    cout << 4 * N - 2 * longest_path << '\n';
}
/*
6
1 1 1 1 1
18

10
1 1 1 2 2 3 4 4 4
30

3
1 2
6

5
1 2 3 3
10
*/
