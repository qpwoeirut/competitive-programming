#include <bits/stdc++.h>

using namespace std;

const int MN = 501;

int R, C, M;
bitset<MN> grid[MN];
bitset<MN> dp[2][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> R >> C >> M;
    for (int i=0; i<R; ++i) {
        string s;
        cin >> s;

        for (int j=0; j<C; ++j) {
            dp[0][i][j] = grid[i][j] = s[j] == '.';
        }
    }
    string moves;
    cin >> moves;

    for (int i=0; i<M; ++i) {
        //for (int r=0; r<R; ++r) { for (int c=0; c<=C; ++c) { cerr << dp[i&1][r][c]; } cerr << endl; } cerr << endl;

        for (int r=0; r<R; ++r) {
            dp[!(i&1)][r].reset();
            if (moves[i] == 'N' || moves[i] == '?') {
                if (r+1 < R) {
                    dp[!(i&1)][r] |= dp[i&1][r+1];
                }
            }
            if (moves[i] == 'S' || moves[i] == '?') {
                if (r > 0) {
                    dp[!(i&1)][r] |= dp[i&1][r-1];
                }
            }
            if (moves[i] == 'W' || moves[i] == '?') {
                dp[!(i&1)][r] |= dp[i&1][r] >> 1;
            }
            if (moves[i] == 'E' || moves[i] == '?') {
                dp[!(i&1)][r] |= dp[i&1][r] << 1;
            }
            dp[!(i&1)][r] &= grid[r];
        }
    }

    int ans = 0;
    for (int i=0; i<R; ++i) {
        ans += dp[M&1][i].count();
    }

    cout << ans << endl;
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
