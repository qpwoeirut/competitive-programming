//brackets.cpp created at 02/22/21 23:37:34

#include <bits/stdc++.h>

using namespace std;

const int MN = 30001;
const int MOD = 1e9 + 9;

int N;
string S;

int dp[2][MN];
int solve() {
    dp[0][0] = 1;
    for (int i=1; i<=N; ++i) {
        for (int j=0; j+j<=N; ++j) {
            dp[i&1][j] = dp[!(i&1)][j+1];
            if (S[i-1] == '(' && j > 0) {
                dp[i&1][j] += dp[!(i&1)][j-1];
                if (dp[i&1][j] >= MOD) dp[i&1][j] -= MOD;
            }
        }
    }
    return dp[N&1][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    cin >> S;

    cout << solve() << endl;
}
/*
50
((((((((((((((((((((((((((((((((((((((((((((((((((
*/
