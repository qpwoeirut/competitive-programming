#include <bits/stdc++.h>

using namespace std;

const int MN = 2005;
const int INIT = 1001001001;

int N, M, C;
int A[MN];
int from[MN], to[MN];

int dp[MN][MN];

void chmx(int& a, const int b) {if (a<b) a=b;}

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> C;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> from[i] >> to[i];
        --from[i]; --to[i];
    }

    for (int i=0; i<MN; ++i) {
        for (int j=0; j<N; ++j) {
            dp[i][j] = -INIT;
        }
    }
    dp[0][0] = 0;
    int ans = 0;
    for (int i=1; i<MN; ++i) {
        for (int j=0; j<M; ++j) {
            chmx(dp[i][to[j]], dp[i-1][from[j]] + A[to[j]]);
        }
        chmx(ans, dp[i][0] - (C * i * i));
    }

    cout << ans << endl;
}
