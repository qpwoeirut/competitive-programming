#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 3003;
const ll MOD = 1e9 + 7;

int n, m, k;
int q;

int G[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    cin >> q;

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            cin >> G[i][j];
        }
    }
    
    for (int i=0; i<q; ++i) {
        int type;
        cin >> type;
        if (type == 0) {
            int r, c, a;
            cin >> r >> c >> a;
            G[r][c] = a;
        } else if (type == 1) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;

            ll total = 0;
            ll ans = 0;
            for (int r=r1; r<=r2; ++r) {
                for (int c=c1; c<=c2; ++c) {
                    total += G[r][c];
                    if (total >= MOD) total -= MOD;
                }
            }
            for (int r=r1; r<=r2; ++r) {
                for (int c=c1; c<=c2; ++c) {
                    ans = (ans + (G[r][c] * (total - G[r][c]))) % MOD;
                }
            }
            ans >>= 1;
            cout << ans << '\n';
        } else assert(0);
    }
}
