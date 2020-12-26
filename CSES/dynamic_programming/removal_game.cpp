//removal_game.cpp created at 12/17/20 20:03:55

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 5005;
const ll INIT = 1e18;

int N;
ll A[MN];
ll dp[MN][MN];

ll solve(const int L, const int R) {
    if (L > R) return 0;
    if (dp[L][R] != -INIT) return dp[L][R];

    dp[L][R] = max(A[L] + min(solve(L+1, R-1), solve(L+2, R)),
                   A[R] + min(solve(L+1, R-1), solve(L, R-2)));
    return dp[L][R];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<=N; ++j) {
            dp[i][j] = -INIT;
        }
    }

    cout << solve(0, N-1) << endl;
}

