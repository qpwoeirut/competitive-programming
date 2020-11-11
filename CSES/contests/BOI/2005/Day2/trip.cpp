#include <bits/stdc++.h>

using namespace std;

const int MN = 1001001;
const int INIT = 1001001001;

struct Edge {
    int u, v;
    int a, b, c, d;

    inline const bool operator<(const Edge& other) const {
        return a < other.a;
    }
};

int N, M, P, T;
Edge edge[MN];
map<int,int> best[MN];
int dp[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> P >> T;
    --P;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].a >> edge[i].b >> edge[i].c >> edge[i].d;
        --edge[i].u;
        --edge[i].v;
    }

    sort(edge, edge+M);

    for (int i=0; i<M; ++i) {
        dp[i] = INIT;
    }

    best[P][T] = T;
    for (int i=M-1; i>=0; --i) {
        auto it = best[edge[i].v].lower_bound(edge[i].d);
        if (it == best[edge[i].v].end()) continue;

        dp[i]= min(dp[i], it->second - edge[i].c);

        it = best[edge[i].u].lower_bound(edge[i].a);
        if (it != best[edge[i].u].end()) {
            best[edge[i].u][edge[i].a] = min(dp[i] + edge[i].b, it->second);
        } else {
            best[edge[i].u][edge[i].a] = dp[i] + edge[i].b;
        }
    }

    auto it = best[0].lower_bound(0);
    if (it != best[0].end()) {
        cout << it->second << endl;
    } else {
        cout << -1 << endl;
    }
}
/*
3 6 2 100
1 3 10 20 30 40
3 2 32 35 95 95
1 1 1 1 7 8
1 3 8 8 9 9
2 2 98 98 99 99
1 2 0 0 99 101

3 2 2 100
1 3 0 0 49 51
3 2 50 51 100 100
*/
