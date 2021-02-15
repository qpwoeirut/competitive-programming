//array_description.cpp created at 12/17/20 18:41:42

#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int MM = 105;
const int MOD = 1e9 + 7;

int N, M;
int A[MN];
int dp[MN][MM];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    if (A[0] == 0) {
        for (int i=1; i<=M; ++i) {
            dp[0][i] = 1;
        }
    } else {
        dp[0][A[0]] = 1;
    }
    for (int i=1; i<N; ++i) {
        if (A[i] == 0) {
            for (int j=1; j<=M; ++j) {
                dp[i][j] = (((dp[i-1][j-1] + dp[i-1][j]) % MOD) + dp[i-1][j+1]) % MOD;
            }
        } else {
            dp[i][A[i]] = (((dp[i-1][A[i]-1] + dp[i-1][A[i]]) % MOD) + dp[i-1][A[i]+1]) % MOD;
        }
    }

    int total = 0;
    for (int i=1; i<=M; ++i) {
        total += dp[N-1][i];
        if (total >= MOD) total -= MOD;
    }
    cout << total << endl;
}

