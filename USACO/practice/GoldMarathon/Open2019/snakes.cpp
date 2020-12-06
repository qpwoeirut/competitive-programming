#include <bits/stdc++.h>

using namespace std;

const int MN = 405;
const int INIT = 1001001001;

int N, K;
int A[MN];

int dp[2][MN][MN];
int min_dp[2][MN];

void chmn(int& a, const int b) {if (a>b) a=b;}

int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            dp[0][i][j] = dp[1][i][j] = INIT;
            min_dp[i][j] = INIT;
        }
    }

    for (int i=0; i<N; ++i) {
        dp[0][0][i] = 0;
    }
    min_dp[0][0] = 0;

    for (int i=1; i<=N; ++i) {
        for (int j=0; j<=K; ++j) {
            min_dp[i&1][j] = INIT;
            for (int k=0; k<N; ++k) {
                if (A[k] >= A[i-1]) {
                    const int change = j ? min_dp[!(i&1)][j-1] + A[k] - A[i-1] : INIT;
                    dp[i&1][j][k] = min(dp[!(i&1)][j][k] + A[k] - A[i-1], change);
                } else {
                    dp[i&1][j][k] = INIT;
                }
                chmn(min_dp[i&1][j], dp[i&1][j][k]);
            }
        }
    }

    int ans = INIT;
    for (int i=0; i<=K; ++i) {
        for (int j=0; j<N; ++j) {
            chmn(ans, dp[N&1][i][j]);
        }
    }
    cout << ans << endl;
}
