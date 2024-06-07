#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int MN = 102;
const int INF = 2001001001;

void chmn(int& a, const int b) {
    a = (a >= b ? b : a);
}

int N, K;
vector<pii> child[MN];
int A[MN];

int depth[MN];
int cost[MN][MN][MN];  // [tree root][root mill][mills used]

int old_cost[MN];
bool visited[MN][MN];
void dfs(int u, int root) {
    if (visited[u][root]) return;
    visited[u][root] = true;

    for (const pii& p: child[u]) {
        depth[p.first] = depth[u] + p.second;
        dfs(p.first, root);
        dfs(p.first, p.first);
    }
    cost[u][root][0] = root == u && root > 0 ? INF : A[u] * (depth[u] - depth[root]);
    for (int mills=1; mills<=K; ++mills) {
        cost[u][root][mills] = 0;
    }
    for (const pii& p: child[u]) {
        copy(cost[u][root], cost[u][root] + K + 1, old_cost);
        for (int i=0; i<=K; ++i) {
            cost[u][root][i] = INF;
            for (int j=0; j<=i; ++j) {
                chmn(cost[u][root][i], old_cost[i - j] + cost[p.first][root][j]);
                if (j) chmn(cost[u][root][i], old_cost[i - j] + cost[p.first][p.first][j]);
            }
        }
    }
    //for (int k=0; k<=K; ++k) cerr << "u, root, mills: " << u << ' ' << root << ' ' << k << ' ' << cost[u][root][k] << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=1; i<=N; ++i) {
        int v, d;
        cin >> A[i] >> v >> d;

        child[v].emplace_back(i, d);
    }

    A[0] = 0;
    depth[0] = 0;
    dfs(0, 0);

    cout << cost[0][0][K] << '\n';
}

