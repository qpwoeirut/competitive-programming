//magenti.cpp created at 12/23/21 20:06:48

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 10;
const int MX = 10000;
const int MOD = 1e9 + 7;

int N, L;
int A[MN];
int dp[1 << MN][MN][MX];

void sub2() {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<L; ++j) {
            dp[1 << i][i][j] = 1;
        }
    }

    for (int mask=0; mask<(1 << N); ++mask) {
        for (int i=0; i<N; ++i) {
            if (((mask >> i) & 1) == 0) continue;
            for (int j=0; j<N; ++j) {
                if ((mask >> j) & 1) continue;
                int dist = max(A[i], A[j]);
                int sum = 0;
                for (int k=dist; k<L; ++k) {
                    sum += dp[mask][i][k - dist];
                    if (sum >= MOD) sum -= MOD;
                    dp[mask | (1 << j)][j][k] += sum;
                    if (dp[mask | (1 << j)][j][k] >= MOD) dp[mask | (1 << j)][j][k] -= MOD;
                }
            }
        }
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<L; ++j) {
            ans += dp[(1 << N) - 1][i][j];
            if (ans >= MOD) ans -= MOD;
        }
    }
    cout << ans << '\n';
}

ll binexp(ll b, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = (ret * b) % MOD;
        p >>= 1;
        b = (b * b) % MOD;
    }
    return ret;
}

ll choose(int n, int k) {
    if (n < k) return 0;
    ll ret = 1;
    for (int i=1; i<=n; ++i) {
        ret = (ret * i) % MOD;
    }
    for (int i=1; i<=k; ++i) {
        ret = (ret * binexp(i, MOD - 2)) % MOD;
    }
    for (int i=1; i<=n-k; ++i) {
        ret = (ret * binexp(i, MOD - 2)) % MOD;
    }
    return ret;
}

void solve() {
    ll fac = 1;
    for (int i=1; i<=N; ++i) {
        fac = (fac * i) % MOD;
    }

    const int extra = L - (N * A[0]) + A[0] - 1;

    cout << (fac * choose(extra + N, N)) % MOD << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> L;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    if (N <= 10) {
        sub2();
    } else {
        solve();
    }
}

