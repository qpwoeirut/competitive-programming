//increasing_subsequence.cpp created at 12/17/20 20:20:23

#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;
const int INIT = 1001001001;

int N;
int A[MN];

int dp[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    fill(dp, dp+N+1, INIT);
    dp[0] = 0;
    for (int i=0; i<N; ++i) {
        const int idx = (lower_bound(dp, dp+N, A[i]) - dp) - 1;

        dp[idx+1] = min(dp[idx+1], A[i]);
    }

    const int ans = (lower_bound(dp, dp+N+1, INIT) - dp) - 1;
    cout << ans << endl;
}

