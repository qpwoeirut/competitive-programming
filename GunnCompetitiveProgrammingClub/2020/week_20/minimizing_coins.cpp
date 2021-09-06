//minimizing_coins.cpp created at 03/23/21 12:11:42

#include <bits/stdc++.h>

using namespace std;

const int MN = 100;
const int MX = 1000006;
const int INIT = 1001001001;

int N, X;
int A[MN];
int dp[MX];

int solve(int cur_sum) {
    if (cur_sum == 0) return 0;
    if (cur_sum < 0) return INIT;
    if (dp[cur_sum] != -1) return dp[cur_sum];

    dp[cur_sum] = INIT;
    for (int i=0; i<N; i++) {
        dp[cur_sum] = min(dp[cur_sum], solve(cur_sum - A[i]) + 1);
    }
    return dp[cur_sum];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    fill(dp, dp+X+1, -1);

    int ans = solve(X);
    ans = (ans == INIT ? -1 : ans);
    cout << ans << endl;
}
