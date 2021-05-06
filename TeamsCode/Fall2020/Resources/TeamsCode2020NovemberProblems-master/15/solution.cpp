#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <utility>
#include <map>
#include <list>
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
#define f first
#define s second

const int maxn = 1e5 + 10, maxm = 1e7 + 10;

int n, m;
vector <int> edge[maxn];
pii st[20][2 * maxn];//sparse table, first int is depth, second is the node number
int loc[maxn], cnt = 0;

void dfs(int u, int p, int d) {
    loc[u] = cnt;
    st[0][cnt++] = make_pair(d, u);
    for (auto v : edge[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        st[0][cnt++] = make_pair(d, u);
    }
}

void set_st() {
    for (int i = 1; i < 20; ++i) {
        for (int j = 0; j + (1 << i) - 1 < cnt; ++j) {
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int find_lca(int a, int b) {
    int la = loc[a], lb = loc[b];
    if (la > lb) swap(la, lb);
    int d = log2(lb - la + 1);
    pii ans = min(st[d][la], st[d][lb - (1 << d) + 1]);
    return ans.s;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0, 1);
    set_st();
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", find_lca(a, b));
    }
}

