#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<ll,ll> Cow;

const int MN = 1005;
const ll INIT = 1e12;

int N, M;
Cow A[MN][2];

ll dp[MN][MN][2];

inline ll get_dist(const Cow& a, const Cow& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=1; i<=N; ++i) {
        cin >> A[i][0].x >> A[i][0].y;
    }
    for (int i=1; i<=M; ++i) {
        cin >> A[i][1].x >> A[i][1].y;
    }

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            dp[i][j][0] = dp[i][j][1] = INIT;
        }
    }

    for (int i=1; i<=N; ++i) {
        for (int j=0; j<=M; ++j) {
            if (i == 1 && j == 0) {
                dp[i][j][0] = 0;
                continue;
            }
            dp[i][j][0] = min(dp[i-1][j][0] + get_dist(A[i-1][0], A[i][0]),
                              dp[i-1][j][1] + get_dist(A[j][1], A[i][0]));
            if (j > 0) {
               dp[i][j][1] = min(dp[i][j-1][0] + get_dist(A[i][0], A[j][1]),
                                 dp[i][j-1][1] + get_dist(A[j-1][1], A[j][1]));
            }

            //cerr << i << ' ' << j << ' ' << dp[i][j][0] << ' ' << dp[i][j][1] << endl;
        }
    }

    cout << dp[N][M][0] << endl;
}
