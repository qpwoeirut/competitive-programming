#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 105;

const ll INF = 1e18;

ll N, K;
ll A[MN];
ll dp[8][MN][MN];
ll mn[8][MN][MN];

ll solve() {
    //for (int i=0; i<N; ++i) { cerr << A[i] << ' '; } cerr << endl;
    for (int i=0; i<=K; ++i) {
        for (int j=0; j<N; ++j) {
            for (int k=0; k<N; ++k) {
                dp[i][j][k] = INF;
                mn[i][j][k] = INF;
            }
        }
    }

    dp[1][0][0] = 0;
    mn[1][0][0] = 0;
    for (int i=1; i<=K; ++i) {
        for (int j=i; j<N; ++j) {
            for (int k=0; k<j; ++k) {
                dp[i][j][k] = dp[i][j-1][k] + A[j] * (j - k);
                mn[i][j][k] = min(k ? mn[i][j][k-1] : INF, dp[i][j][k]);

                //cerr << i << ' ' << j << ' ' << k << ' ' << dp[i][j][k] << ' ' << mn[i][j][k] << endl;
            }
            dp[i][j][j] = mn[i-1][j-1][j-1];
            mn[i][j][j] = min(j ? mn[i][j][j-1] : INF, dp[i][j][j]);

            //cerr << i << ' ' << j << ' ' << j << ' ' << dp[i][j][j] << ' ' << mn[i][j][j] << endl;
        }
    }
    ll ans = INF;
    for (int i=0; i<N; ++i) {
        //cerr << K << ' ' << N-1 << ' ' << i << ' ' << dp[K][N-1][i] << endl;
        ans = min(ans, dp[K][N-1][i]);
    }
    //cerr << ans << endl;
    return ans;
}

int main() {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ll ans = INF;
    for (int i=0; i<N; ++i) {
        ans = min(ans, solve());
        rotate(A, A+1, A+N);
    }

    cout << ans << endl;
}
