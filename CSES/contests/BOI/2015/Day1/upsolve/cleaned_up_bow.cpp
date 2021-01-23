//bow.cpp created at 01/11/21 21:28:23

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 12;
const int MX = 305;
const int MS = 11;
const int SPARE = 10;
const int STRIKE = 10;

int N;
string S;
int A[MN];

ll dp[MN][MX][MS][MS];

inline const bool good(const int idx, const char val) {
    return S[idx] == val || S[idx] == '?';
}
inline const bool ok(const int idx, const int val) {
    return A[idx] == -1 || A[idx] == val;
}

ll solve() {
    for (int i=0; i<=N; ++i) {
        for (int j=0; j<MX; ++j) {
            for (int k=0; k<MS; ++k) {
                for (int l=0; l<MS; ++l) {
                    dp[i][j][k][l] = 0;
                }
            }
        }
    }

    for (int i=0; i<MS; ++i) {
        for (int j=0; j<MS; ++j) {
            dp[0][0][i][j] = 1;
        }
    }

    for (int i=0; i<N-1; ++i) {
        for (int j=0; j<MX; ++j) {
            if (i > 0 && !ok(i, j)) continue;
            if (good(2*i, 'x') && good(2*i+1, '-')) {
                for (int k=0; k<MS; ++k) { // strike
                    if (dp[i][j][STRIKE][k] == 0) continue;
                    for (int l=0; l<MS; ++l) {
                        const int score = j + 10 + k + l;
                        dp[i+1][score][k][l] += dp[i][j][STRIKE][k];
                    }
                }
            }
            for (int a=0; a<10; ++a) {
                if (!good(2 * i, '0' + a)) continue;

                if (good(2*i + 1, '/')) { // spare
                    for (int k=0; k<MS; ++k) {
                        const int score = j + 10 + k;
                        if (dp[i][j][a][10-a] == 0 || !ok(i+1, score)) continue;
                        for (int l=0; l<MS; ++l) {
                            dp[i+1][score][k][l] += dp[i][j][a][10-a];
                        }
                    }
                }
                for (int b=0; a+b<10; ++b) {
                    if (good(2*i + 1, '0' + b)) { // other
                        const int score = j + a + b;
                        if (!ok(i+1, score)) continue;
                        for (int k=0; k<MS; ++k) {
                            if (dp[i][j][a][b] == 0) continue;
                            for (int l=0; l<MS; ++l) {
                                dp[i+1][score][k][l] += dp[i][j][a][b];
                            }
                        }
                    }
                }
            }
        }
    }

    ll ans = 0;
    const int i = N-1;
    for (int j=0; j<MX; ++j) {
        if (!ok(i, j)) continue;
        if (good(2*i, 'x') && good(2*i + 1, 'x') && good(2*i + 2, 'x')) { // xxx
            const int score = j + 30;
            if (ok(N, score)) ans += dp[i][j][STRIKE][STRIKE];
        }

        for (int a=0; a<10; ++a) {
            if (good(2*i, 'x')) {
                if (good(2*i + 1, 'x') && good(2*i + 2, '0' + a)) { // xxA
                    const int score = j + 20 + a;
                    if (ok(N, score)) ans += dp[i][j][STRIKE][STRIKE];
                }

                if (good(2*i + 1, '0' + a)) {
                    if (good(2*i + 2, '/')) { // xA/
                        const int score = j + 20;
                        if (ok(N, score)) ans += dp[i][j][STRIKE][a];
                    }

                    for (int b=0; a+b<10; ++b) {
                        if (good(2*i + 2, '0' + b)) { // xAB
                            const int score = j + 10 + a + b;
                            if (ok(N, score)) ans += dp[i][j][STRIKE][a];
                        }
                    }
                }
            }

            if (good(2*i, '0' + a)) {
                if (good(2*i + 1, '/')) {
                    if (good(2*i + 2, 'x')) { // A/x
                        const int score = j + 20;
                        if (ok(N, score)) ans += dp[i][j][a][10-a];
                    }
                    for (int b=0; b<10; ++b) {
                        if (good(2*i + 2, '0' + b)) { // A/B
                            const int score = j + 10 + b;
                            if (ok(N, score)) ans += dp[i][j][a][10-a];
                        }
                    }
                }
                for (int b=0; a+b<10; ++b) {
                    if (good(2*i + 1, '0' + b) && good(2*i + 2, '-')) { // AB-
                        const int score = j + a + b;
                        if (ok(N, score)) ans += dp[i][j][a][b];
                    }
                }
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int test_cases;
    cin >> test_cases;
    for (int t=1; t<=test_cases; ++t) {
        cin >> N;
        cin >> S;
        for (int i=1; i<=N; ++i) {
            cin >> A[i];
        }
        cout << solve() << endl;
    }
}

/*
2
2
22??2
-1 -1

2
?5?1/
6 -1


3

10
08x-7/2/x?x-23??1/???
8 -1 40 60 82 97 102 110 120 140

5
x-x-23?/00-
22 37 42 52 52

6
x-x-x-x-x-xxx
-1 -1 -1 -1 -1 -1
*/

