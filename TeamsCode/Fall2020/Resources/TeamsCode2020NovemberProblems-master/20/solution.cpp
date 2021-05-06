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

const int maxn = 210;

int n, m;
int d[maxn][maxn], c[maxn][maxn];
bool ans[maxn];

int main() {
    memset(d, 0x3f, sizeof(d));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v, dst;
        scanf("%d%d%d", &u, &v, &dst);
        d[u][v] = d[v][u] = dst;
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (i == k) continue;
            for (int j = 1; j <= n; ++j) {
                if (i == j || j == k) continue;
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    c[i][j] = k;
                }
                else if (d[i][j] == d[i][k] + d[k][j]) {
                    c[i][j] = 0;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (c[i][j]) ans[c[i][j]] = 1;
        }
    }
    bool chk = 0;
    for (int i = 1; i <= n; ++i) {
        if (ans[i]) {
            printf("%d ", i);
            chk = 1;
        }
    }
    if (!chk) printf("No");
    printf("\n");
}

