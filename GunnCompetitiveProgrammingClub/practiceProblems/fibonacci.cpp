#include <iostream>

using namespace std;

const int MAXN = 1e6;
const int MOD = 1e9 + 7;

int dp[MAXN + 1];

long long fib(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;

    if (dp[n] != -1) return dp[n];

    dp[n] = (fib(n - 1) + fib(n - 2)) % MOD;
    return dp[n];
}

int main() {
    int N;
    cin >> N;

    fill(dp, dp+N+1, -1);

    cout << fib(N) << '\n';
}

