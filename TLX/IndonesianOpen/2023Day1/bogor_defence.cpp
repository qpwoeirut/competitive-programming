//bogor_defence.cpp created at 08/29/23 15:24:44

#include <bits/stdc++.h>

using namespace std;

const int MN = 200001;
int N;
int A[MN];

int dp[MN];
int max_dp[MN];
int max_offset[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }

    for (int i=1; i<=N; ++i) {
        if (i >= A[i]) {
            dp[i] = max(max_dp[i - A[i]], max_offset[i - A[i]]) + 1;
            max_offset[i - A[i]] = max(max_offset[i - A[i]], dp[i]);
        } else {
            dp[i] = -1e9;
        }
        max_dp[i] = max(max_dp[i - 1], dp[i]);
    }

    cout << N - max_dp[N] << '\n';
}

