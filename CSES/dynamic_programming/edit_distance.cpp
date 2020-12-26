//edit_distance.cpp created at 12/17/20 19:05:03

#include <bits/stdc++.h>

using namespace std;

const int MN = 5005;
const int INIT = 1001001001;

string S, T;

int dp[MN][MN];

void chmn(int& a, const int b) {
    if (a>b) a=b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> S >> T;
    const int N = S.size();
    const int M = T.size();

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            dp[i][j] = INIT;
        }
    }

    dp[0][0] = 0;
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            chmn(dp[i+1][j], dp[i][j] + 1);
            chmn(dp[i][j+1], dp[i][j] + 1);
            if (i < N && j < M) {
                chmn(dp[i+1][j+1], dp[i][j] + (S[i] != T[j]));
            }
        }
    }

    cout << dp[N][M] << endl;
}
