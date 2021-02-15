//dice_combinations.cpp created at 12/16/20 22:16:04

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N;
ll dp[6];

int main() {
    cin >> N;
    dp[0] = 1;
    for (int i=1; i<=N; ++i) {
        dp[i%6] = (dp[0] + dp[1] + dp[2] + dp[3] + dp[4] + dp[5]) % MOD;
    }

    cout << dp[N % 6] << endl;
}
