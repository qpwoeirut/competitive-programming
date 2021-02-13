//programmers.cpp created at 01/29/21 22:48:53

#include <bits/stdc++.h>

using namespace std;

const int MN = 2005;
const int INIT = 1001001001;

int N, K;
int A[MN];
int dp[MN][MN];
int pref[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=K; ++j) {
            dp[i][j] = INIT;
        }
    }
    for (int i=0; i<=N; ++i) {
        dp[i][0] = 0;
    }
    for (int j=0; j<=K; ++j) {
        pref[j] = INIT;
    }
    pref[0] = 0;

    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=K; ++j) {
            dp[i][j] = dp[i-1][j];
            if (i > 1) {
                dp[i][j] = min(dp[i][j], pref[j-1] + A[i-1] - A[i-2]);
            }
        }
        for (int j=1; j<=K; ++j) {
            pref[j] = min(pref[j], dp[i-1][j]);
        }
    }

    //for (int i=0; i<=N; ++i) { for (int j=0; j<=K; ++j) { cerr << dp[i][j] << ' '; } cerr << endl; }
    cout << dp[N][K] << endl;
}

