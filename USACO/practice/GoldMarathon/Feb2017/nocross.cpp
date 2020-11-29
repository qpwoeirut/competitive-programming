#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;

int N;
int A[MN], B[MN];

int dp[MN][MN];

int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        cin >> B[i];
    }

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if (abs(A[i-1] - B[j-1]) <= 4) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
            }
        }
    }

    cout << dp[N][N] << endl;
}
