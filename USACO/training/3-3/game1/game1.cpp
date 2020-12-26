/*
ID: zhongbr1
TASK: game1
LANG: C++14
*/

//game1.cpp created at 12/23/20 13:42:35

#include <bits/stdc++.h>

using namespace std;

const int MN = 105;

int N;
int A[MN];

int dp[MN][MN];

int main() {
    freopen("game1.in", "r", stdin);
    freopen("game1.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    int sum = 0;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        sum += A[i];
        dp[i][i] = A[i];
    }
    for (int i=2; i<=N; ++i) {
        for (int L=0; L+i<=N; ++L) {
            const int R = L + i - 1;
            dp[L][R] = max(A[L] + min(dp[L+2][R], dp[L+1][R-1]), A[R] + min(dp[L][R-2], dp[L+1][R-1]));
        }
    }

    const int ans = dp[0][N-1];
    cout << dp[0][N-1] << ' ' << sum - ans << endl;
}
