#include <bits/stdc++.h>

using namespace std;

const int MN = 51;
const int INF = 1001001001;

void chmn(int& a, const int b) {
    a = (a < b) ? a : b;
}

int N, M, K;
char G[MN][MN];
string A[MN];

int dp[MN][MN][3][MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=0; i<N; ++i) {
        for (int j=0; j<M; ++j) {
            cin >> G[i][j];
        }
    }

    for (int k=0; k<K; ++k) {
        cin >> A[k];
    }

    for (int r=0; r<N; ++r) {
        for (int c=0; c<M; ++c) {
            for (int d=0; d<3; ++d) {
                for (int k=0; k<K; ++k) {
                    for (int l=0; l<MN; ++l) {
                        dp[r][c][d][k][l] = INF;
                    }
                }
            }
        }
    }

    for (int c=0; c<M; ++c) {
        for (int k=0; k<K; ++k) {
            if (A[k][0] == G[0][c]) {
                dp[0][c][0][k][0] = 1;
            }
        }
    }

    for (int r=0; r<N; ++r) {
        for (int c=0; c<M; ++c) {
            for (int d=0; d<3; ++d) {
                for (int k=0; k<K; ++k) {
                    for (int l=0; l + 1<A[k].size(); ++l) {
                        if (dp[r][c][d][k][l] == INF) continue;
                        if (r + 1 < N && A[k][l + 1] == G[r + 1][c]) {
                            chmn(dp[r + 1][c][0][k][l + 1], dp[r][c][d][k][l] + 1);
                        }
                        if (c     > 0 && A[k][l + 1] == G[r][c - 1] && d != 2) {
                            chmn(dp[r][c - 1][1][k][l + 1], dp[r][c][d][k][l] + 1);
                        }
                        if (c + 1 < M && A[k][l + 1] == G[r][c + 1] && d != 1) {
                            chmn(dp[r][c + 1][2][k][l + 1], dp[r][c][d][k][l] + 1);
                        }
                        //cerr << r << ' ' << c << ' ' << d << ' ' << k << ' ' << l << ' ' << dp[r][c][d][k][l] << '\n';
                    }
                    for (int k2=0; k2<K; ++k2) {
                        const int last = A[k].size() - 1;
                        if (r + 1 < N && A[k2][0] == G[r + 1][c]) {
                            chmn(dp[r + 1][c][0][k2][0], dp[r][c][d][k][last] + 1);
                        }
                        if (c     > 0 && A[k2][0] == G[r][c - 1] && d != 2) {
                            chmn(dp[r][c - 1][1][k2][0], dp[r][c][d][k][last] + 1);
                        }
                        if (c + 1 < M && A[k2][0] == G[r][c + 1] && d != 1) {
                            chmn(dp[r][c + 1][2][k2][0], dp[r][c][d][k][last] + 1);
                        }
                    }
                }
            }
        }
        for (int c=M-1; c>=0; --c) {
            for (int d=0; d<3; ++d) {
                for (int k=0; k<K; ++k) {
                    for (int l=0; l + 1<A[k].size(); ++l) {
                        if (dp[r][c][d][k][l] == INF) continue;
                        if (r + 1 < N && A[k][l + 1] == G[r + 1][c]) {
                            chmn(dp[r + 1][c][0][k][l + 1], dp[r][c][d][k][l] + 1);
                        }
                        if (c     > 0 && A[k][l + 1] == G[r][c - 1] && d != 2) {
                            chmn(dp[r][c - 1][1][k][l + 1], dp[r][c][d][k][l] + 1);
                        }
                        if (c + 1 < M && A[k][l + 1] == G[r][c + 1] && d != 1) {
                            chmn(dp[r][c + 1][2][k][l + 1], dp[r][c][d][k][l] + 1);
                        }
                        //cerr << r << ' ' << c << ' ' << d << ' ' << k << ' ' << l << ' ' << dp[r][c][d][k][l] << '\n';
                    }
                    for (int k2=0; k2<K; ++k2) {
                        const int last = A[k].size() - 1;
                        if (r + 1 < N && A[k2][0] == G[r + 1][c]) {
                            chmn(dp[r + 1][c][0][k2][0], dp[r][c][d][k][last] + 1);
                        }
                        if (c     > 0 && A[k2][0] == G[r][c - 1] && d != 2) {
                            chmn(dp[r][c - 1][1][k2][0], dp[r][c][d][k][last] + 1);
                        }
                        if (c + 1 < M && A[k2][0] == G[r][c + 1] && d != 1) {
                            chmn(dp[r][c + 1][2][k2][0], dp[r][c][d][k][last] + 1);
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    for (int c=0; c<M; ++c) {
        for (int d=0; d<3; ++d) {
            for (int k=0; k<K; ++k) {
                const int last = A[k].size() - 1;
                chmn(ans, dp[N - 1][c][d][k][last]);
            }
        }
    }

    if (ans == INF) {
        cout << "impossible\n";
    } else {
        cout << ans << '\n';
    }
}
/*
4 4 1
A B C D
X X F E
X X A B
F E D C
ABCDEF

4 4 1
A B C D
X C F E
X D A B
F E D C
ABCDEF

4 4 1
A B C D
X C F E
X D A B
X E D C
ABCDEF
*/
