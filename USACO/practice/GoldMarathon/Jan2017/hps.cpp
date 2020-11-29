#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N, K;
int A[MN];

int dp[MN][25][3];
void chmx(int& a, const int b) {if (a<b) a=b;}

int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        char c;
        cin >> c;
        if (c == 'H') A[i] = 0;
        else if (c == 'P') A[i] = 1;
        else if (c == 'S') A[i] = 2;
        else assert(false);
    }

    int ans = 0;
    for (int i=1; i<=N; ++i) {
        for (int j=0; j<=K; ++j) {
            for (int k=0; k<3; ++k) {
                dp[i][j][k] = dp[i-1][j][k] + (A[i-1] == k);
                if (j > 0) {
                    for (int prev=0; prev<3; ++prev) {
                        if (prev == k) continue;
                        chmx(dp[i][j][k], dp[i-1][j-1][prev] + (A[i-1] == k));
                    }
                }
                chmx(ans, dp[i][j][k]);
            }
        }
    }

    cout << ans << endl;
}
