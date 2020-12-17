//removing_digits.cpp created at 12/16/20 22:30:23

#include <bits/stdc++.h>

using namespace std;

const int MN = 1000005;

int N;
int dp[MN];

int main() {
    cin >> N;

    fill(dp, dp+N, N);
    for (int i=N; i>0; --i) {
        int x = i;
        while (x > 0) {
            int idx = i - (x % 10);
            if (idx >= 0) {
                dp[idx] = min(dp[idx], dp[i] + 1);
            }
            x /= 10;
        }
    }
    cout << dp[0] << endl;
}
