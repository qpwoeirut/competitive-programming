//jumpy.cpp created at 02/18/21 20:00:14

#include <bits/stdc++.h>

using namespace std;

const int MN = 502;
const int X = 21;

int N, M;
string G[MN];
int id[MN][MN];

int8_t dp[2][1 << X][X];
bool ans[2][MN][MN];
int solve(const int player, const int mask, const int row, const int col) {
    if (dp[player][mask][row*M + col] != -1) return dp[player][mask][row*M + col];

    dp[player][mask][row*M + col] = 0;
    if (player == 0) {
        for (int r=row-1; r>=0; --r) {
            if (G[r][col] == '#') break;
            if (((mask >> id[r][col]) & 1) == 0) {
                dp[player][mask][row*M + col] |= !solve(player ^ 1, mask | (1 << id[row][col]), r, col);
            } else {
                dp[player][mask][row*M + col] = 1;
            }
        }
        for (int r=row+1; r<N; ++r) {
            if (G[r][col] == '#') break;
            if (((mask >> id[r][col]) & 1) == 0) {
                dp[player][mask][row*M + col] |= !solve(player ^ 1, mask | (1 << id[row][col]), r, col);
            } else {
                dp[player][mask][row*M + col] = 1;
            }
        }
    } else {
        for (int c=col-1; c>=0; --c) {
            if (G[row][c] == '#') break;
            if (((mask >> id[row][c]) & 1) == 0) {
                dp[player][mask][row*M + col] |= !solve(player ^ 1, mask | (1 << id[row][col]), row, c);
            } else {
                dp[player][mask][row*M + col] = 1;
            }
        }
        for (int c=col+1; c<M; ++c) {
            if (G[row][c] == '#') break;
            if (((mask >> id[row][c]) & 1) == 0) {
                dp[player][mask][row*M + col] |= !solve(player ^ 1, mask | (1 << id[row][col]), row, c);
            } else {
                dp[player][mask][row*M + col] = 1;
            }
        }
    }
    //cerr << player << ' ' << bitset<30>(mask).to_string() << ' ' << row << ' ' << col << endl;
    return dp[player][mask][row*M + col];
}

int main() {
    freopen("jumpy.in", "r", stdin);
    freopen("jumpy.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> G[i];
        for (int j=0; j<M; ++j) {
            id[i][j] = i*M + j;
        }
    }

    if (N*M > X) {
        for (int r=0; r<N; ++r) {
            for (int c=0; c<M; ++c) {
                assert(G[r][c] == '.');
                if (N < M) {
                    cout << 'S';
                } else if (N > M) {
                    cout << 'T';
                } else {
                    cout << 'B';
                }
            }
            cout << '\n';
        }
        return 0;
    }

    for (int i=0; i<(1 << X); ++i) {
        for (int j=0; j<X; ++j) {
            dp[0][i][j] = dp[1][i][j] = -1;
        }
    }

    for (int r=0; r<N; ++r) {
        for (int c=0; c<M; ++c) {
            if (G[r][c] != '#') {
                ans[0][r][c] = solve(0, 0, r, c) || !solve(1, 0, r, c);
                ans[1][r][c] = solve(1, 0, r, c) || !solve(0, 0, r, c);
            }
        }
    }
    for (int r=0; r<N; ++r) {
        for (int c=0; c<M; ++c) {
            if (G[r][c] == '#') {
                cout << '#';
            } else if (ans[0][r][c] && ans[1][r][c]) {
                cout << 'B';
            } else if (ans[0][r][c]) {
                cout << 'T';
            } else if (ans[1][r][c]) {
                cout << 'S';
            } else {
                cout << 'N';
            }
        }
        cout << '\n';
    }
}

/*
9 9
....#..#.
.####..#.
.......#.
.#..#.##.
.#..#....
########.
....#....
##.##.##.
.......#.

5 5
...#.
.###.
...#.
##.#.
.....

3 3
...
...
...
*/
