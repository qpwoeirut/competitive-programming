#include <bits/stdc++.h>

using namespace std;

const int MN = 101;

int N;
int A[MN];

void chmn(int& a, const int b) {if (a>b) a=b;}
int dp[MN][MN][MN];

int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=N; ++j) {
            for (int k=0; k<=N; ++k) {
                dp[i][j][k] = MN;
            }
        }
    }
    dp[0][0][0] = A[0] != 0;
    for (int i=0; i+1<N; ++i) {
        for (int j=0; j<N; ++j) {
            for (int k=0; k<=i; ++k) {
                chmn(dp[i+1][j+1][0], dp[i][j][k] + (A[i+1] != 0));
                chmn(dp[i+1][j][k+1], dp[i][j][k] + (A[i+1] != k+1));
            }
        }
    }

    for (int i=0; i<N; ++i) {
        int ans = MN;
        for (int j=0; j<N; ++j) {
            chmn(ans, dp[N-1][i][j]);
        }
        cout << ans << '\n';
    }
}
