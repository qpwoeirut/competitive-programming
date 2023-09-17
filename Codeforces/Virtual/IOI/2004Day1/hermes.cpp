//hermes.cpp created at 09/15/23 14:42:59

#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
#define x first
#define y second

const int MN = 20000;
const int MX = 2001;
const int OFFSET = 1000;
const int INF = 1001001001;

int N;
pii A[MN];

int dp[2][MX][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].x >> A[i].y;
        A[i].x += OFFSET;
        A[i].y += OFFSET;
    }

    for (int xy=0; xy<MX; ++xy) {
        dp[0][xy][0] = dp[0][xy][1] = dp[1][xy][0] = dp[1][xy][1] = INF;
    }
    dp[0][OFFSET][0] = dp[0][OFFSET][1] = 0;
    for (int i=0; i<N; ++i) {
        const int j = (i&1) ^ 1;
        for (int xy=0; xy<MX; ++xy) {
            dp[j][xy][0] = dp[j][xy][1] = INF;
        }

        for (int xy=0; xy<MX; ++xy) {
            for (int k=0; k<2; ++k) {
                if (dp[i&1][xy][k] < INF) {
                    const int x = k ? (i ? A[i - 1].x : OFFSET) : xy;
                    const int y = k ? xy : (i ? A[i - 1].y : OFFSET);
                    dp[j][x][0] = min(dp[j][x][0], dp[i&1][xy][k] + abs(A[i].y - y));
                    dp[j][y][1] = min(dp[j][y][1], dp[i&1][xy][k] + abs(A[i].x - x));
                }
            }
        }
    }

    int ans = INF;
    for (int xy=0; xy<MX; ++xy) {
        ans = min(ans, min(dp[N & 1][xy][0], dp[N & 1][xy][1]));
    }
    cout << ans << '\n';
}

