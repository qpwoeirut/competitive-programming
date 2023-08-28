#include <bits/stdc++.h>

using namespace std;

const int MN = 1003;
const int INF = 51001;

int N;
int A[MN][MN];
const int B[3] = {2, 5, 0};

int dp[3][MN][MN];
char path[3][MN][MN];

int pw_of(int x, int b) {
    if (b == 0) return x > 0 ? 1 : -INF;
    int ret = 0;
    while (x % b == 0 && x > 0) {
        x /= b;
        ++ret;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            cin >> A[i][j];
        }
    }

    for (int bi=0; bi<3; ++bi) {
        for (int i=0; i<=N; ++i) {
            for (int j=0; j<=N; ++j) {
                dp[bi][i][j] = INF;
            }
        }
        dp[bi][0][0] = dp[bi][1][0] = dp[bi][0][1] = 0;
        for (int i=1; i<=N; ++i) {
            for (int j=1; j<=N; ++j) {
                path[bi][i][j] = dp[bi][i-1][j] <= dp[bi][i][j-1] ? 'D' : 'R';
                dp[bi][i][j] = min(dp[bi][i-1][j], dp[bi][i][j-1]) + pw_of(A[i-1][j-1], B[bi]);
            }
        }
    }

    int bi = dp[0][N][N] > dp[1][N][N];
    if (dp[bi][N][N] > 1 && dp[2][N][N] < 0) bi = 2;
    string way = "";
    int r = N, c = N;
    while (r > 1 || c > 1) {
        way.push_back(path[bi][r][c]);
        if (path[bi][r][c] == 'D') --r;
        else if (path[bi][r][c] == 'R') --c;
        else assert(0);
    }

    reverse(way.begin(), way.end());
    int ans = bi == 2 ? 1 : dp[bi][N][N];
    cout << ans << '\n' << way << '\n';
}
