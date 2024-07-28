#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

using ll = long long;
using pll = pair<ll,ll>;

const int MAX_N = 1000000000;
const int MAX_A = 2500000;
const int MAX_B = 31;
const int MAX_C = 66000;
ll dp[MAX_B][MAX_C];

void chmx(ll& a, ll b) {
    a = (a >= b ? a : b);
}
void chmx(int& a, int b) {
    a = (a >= b ? a : b);
}
void chmn(int& a, int b) {
    a = (a <= b ? a : b);
}
void chmn(ll& a, ll b) {
    a = (a <= b ? a : b);
}

pll cost[MAX_B * MAX_C];

void solve() {
    ll A, B, C, N;
    cin >> A >> B >> C >> N;

    for (int b=0; b<MAX_B; ++b) {
        for (int c=0; c<MAX_C; ++c) {
            cost[b * MAX_C + c] = pll(dp[b][c], b * B + c * C);
        }
    }
    sort(cost, cost + MAX_B * MAX_C);
    for (int i=MAX_B * MAX_C - 1; i > 0; --i) {
        chmn(cost[i - 1].second, cost[i].second);
    }

    ll ans = 1ll * N * A;
    for (int a = 1; a <= MAX_A; ++a) {
        const int target = (N + a - 1) / a;
        const ll cst = lower_bound(cost, cost + MAX_B * MAX_C, pll(target, 0))->second;
        chmn(ans, a * A + cst);
    }
    cout << ans << "\n";
}
int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int j=0; j<MAX_C; ++j) {
        dp[1][j] = j + 1;
    }
    for (int i=2; i<MAX_B; ++i) {
        dp[i][0] = 1;
        for (int j=1; j<MAX_C; ++j) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][(i - 1) * j / i];
        }
    }

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

/*
8
1 1 1 1000000000
1000000 1 1 1000000000
1 1000000 1 1000000000
1 1 1000000 1000000000
1000000 1000000 1 1000000000
1000000 1 1000000 1000000000
1 1000000 1000000 1000000000
1000000 1000000 1000000 1000000000

8
1 1 1 1000000
1000000 1 1 1000000
1 1000000 1 1000000
1 1 1000000 1000000
1000000 1000000 1 1000000
1000000 1 1000000 1000000
1 1000000 1000000 1000000
1000000 1000000 1000000 1000000
*/
