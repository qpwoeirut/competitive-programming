#include <bits/stdc++.h>

using namespace std;

const int MN = 105;

int R, C, M;
string s;
bool G[MN][MN];
bool dp[MN][MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C >> M;

    for (int i=1; i<=R; ++i) {
        for (int j=1; j<=C; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '.';

            for (int k=0; k<=M; ++k) {
                dp[k][i][j] = false;
            }
        }
    }

    cin >> s;

    for (int i=1; i<=R; ++i) {
        for (int j=1; j<=C; ++j) {
            dp[0][i][j] = G[i][j];
        }
    }

    for (int m=0; m<M; ++m) {
        for (int i=1; i<=R; ++i) {
            for (int j=1; j<=C; ++j) {
                if (!G[i][j]) {
                    dp[m][i][j] = false;
                }
                if (!dp[m][i][j]) continue;
                if (s[m] == 'N' || s[m] == '?') {
                    dp[m+1][i-1][j] = true;
                }
                if (s[m] == 'S' || s[m] == '?') {
                    dp[m+1][i+1][j] = true;
                }
                if (s[m] == 'W' || s[m] == '?') {
                    dp[m+1][i][j-1] = true;
                }
                if (s[m] == 'E' || s[m] == '?') {
                    dp[m+1][i][j+1] = true;
                }
            }
        }
    }
    int ans = 0;
    for (int i=1; i<=R; ++i) {
        for (int j=1; j<=C; ++j) {
            if (G[i][j] && dp[M][i][j]) ++ans;
        }
    }

    cout << ans << endl;

    //for (int m=0; m<=M; ++m) { for (int i=1; i<=R; ++i) { for (int j=1; j<=C; ++j) cerr << dp[m][i][j]; cerr << endl;} cerr << endl;}
}
/*
5 9 7
...##....
..#.##..#
..#....##
.##...#..
....#....
WS?EE??
*/
