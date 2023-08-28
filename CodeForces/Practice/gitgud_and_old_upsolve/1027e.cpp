//1027e.cpp created at 01/22/21 23:22:50

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 505;
const int MK = 250005;
const ll MOD = 998244353;

ll N, K;
ll row[MN];
ll dp[2][MK];

ll calc(const int k, const int start) {
    for (int j=0; j<=k; ++j) {
        dp[0][j] = dp[1][j] = 0;
    }
    dp[1][1] = start;
    for (int i=1; i<N; ++i) {
        const int nxt = !(i&1);
        fill(dp[nxt], dp[nxt] + k+1, 0);
        for (int j=1; j<=i && j<=k; ++j) {
            if (dp[i&1][j] == 0) continue;
            if (j < k) {
                dp[nxt][j+1] += dp[i&1][j];
                if (dp[nxt][j+1] >= MOD) dp[nxt][j+1] -= MOD;
            }
            dp[nxt][1] += dp[i&1][j];
            if (dp[nxt][1] >= MOD) dp[nxt][1] -= MOD;
        }
    }
    ll ret = 0;
    for (int i=0; i<=k; ++i) {
        ret += dp[N&1][i];
        if (ret >= MOD) ret -= MOD;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;

    for (int i=N; i>=1; --i) {
        row[i] = calc(i, 2);
        if (i < N) {
            row[i+1] -= row[i];
            if (row[i+1] < 0) row[i+1] += MOD;
        }
    }

    //for (int i=1; i<=N; ++i) { cerr << row[i] << ' '; } cerr << endl;

    ll ans = 0;
    for (int i=1; i<=N; ++i) {
        const int mx = (K-1) / i;
        ans = (ans + calc(mx, 1) * row[i]) % MOD;
    }

    cout << ans << endl;
}

