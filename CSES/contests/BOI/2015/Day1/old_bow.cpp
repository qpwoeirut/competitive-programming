//bow.cpp created at 01/11/21 19:16:33

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 12;
const int MX = 305;
const int STRIKE = 2;
const int SPARE = 1;
const int NONE = 0;

int N;
string S;
int A[MN];

ll dp[MN][MX][3][3];

bool good(const int idx, const char val) {
    return S[idx] == val || S[idx] == '?';
}
bool ok(const int idx, const int val) {
    return A[idx] == -1 || A[idx] == val;
}

int sc(const int a, const int b, const int c, const int k, const int l) {
    int score = a + b + c;
    if (k == STRIKE && l == STRIKE) score += a;
    if (l == STRIKE) score += a + b;
    else if (l == SPARE) score += a;
    return score;
}

void solve() {
    cin >> N;
    cin >> S;
    A[0] = 0;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<=N; ++i) {
        for (int j=0; j<MX; ++j) {
            for (int k=0; k<3; ++k) {
                dp[i][j][k][0] = dp[i][j][k][1] = dp[i][j][k][2] = 0;
            }
        }
    }

    dp[0][0][0][0] = 1;
    for (int i=0; i<N-1; ++i) {
        for (int j=0; j<MX; ++j) {
            for (int k=0; k<3; ++k) {
                for (int l=0; l<3; ++l) {
                    if (dp[i][j][k][l] == 0) continue;
                    cerr << i << ' ' << j << ' ' << k << ' ' << l << " = " << dp[i][j][k][l] << endl;

                    if (good(2*i, 'x') && good(2*i+1, '-')) {
                        cerr << "strike" << endl;
                        int score = j + sc(10, 0, 0, k, l);
                        dp[i+1][score][l][STRIKE] += dp[i][j][k][l];
                    }
                    for (int a=0; a<10; ++a) {
                        if (!good(2 * i, '0' + a)) continue;

                        if (good(2*i + 1, '/')) {
                            cerr << "spare a=" << a << endl;
                            int score = j + sc(a, 10-a, 0, k, l);
                            dp[i+1][score][l][SPARE] += dp[i][j][k][l];
                        }
                        for (int b=0; a+b<10; ++b) {
                            if (good(2*i + 1, '0' + b)) {
                                cerr << "a,b=" << a << "," << b << endl;
                                int score = j + sc(a, b, 0, k, l);
                                dp[i+1][score][l][NONE] += dp[i][j][k][l];
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
        for (int k=0; k<3; ++k) {
            for (int l=0; l<3; ++l) {
                if (dp[i][j][k][l] == 0) continue;
                if (good(2*i, 'x') && good(2*i + 1, 'x') && good(2*i + 2, 'x')) {
                    int score = j + sc(10, 10, 10, k, l);
                    if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                }

                for (int a=0; a<10; ++a) {
                    if (good(2*i, 'x')) {
                        if (good(2*i + 1, 'x') && good(2*i + 2, '0' + a)) {
                            int score = j + sc(10, 10, a, k, l);
                            if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                        }

                        if (good(2*i + 1, '0' + a)) {
                            if ( good(2*i + 2, '/')) {
                                int score = j + sc(10, a, 10 - a, k, l);
                                if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                            }

                            for (int b=0; a+b<10; ++b) {
                                if (good(2*i + 2, '0' + b)) {
                                    int score = j + sc(10, a, b, k, l);
                                    if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                                }
                            }
                        }
                    }

                    if (good(2*i, '0' + a)) {
                        if (good(2*i + 1, '/')) {
                            if (good(2*i + 2, 'x')) {
                                int score = j + sc(a, 10-a, 10, k, l);
                                if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                            }
                            for (int b=0; a+b<10; ++b) {
                                if (good(2*i + 2, '0' + b)) {
                                    int score = j + sc(a, 10-a, b, k, l);
                                    if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                                }
                            }
                        }
                        for (int b=0; a+b<10; ++b) {
                            if (good(2*i + 1, '0' + b) && good(2*i + 2, '-')) {
                                int score = j + sc(a, b, 0, k, l);
                                if (A[N] == -1 || A[N] == score) ans += dp[i][j][k][l];
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;
}

int main() {
    int test_case;
    cin >> test_case;
    for (int t=1; t<=test_case; ++t) {
        cerr << "\n------------" << endl;
        solve();
    }
}

/*
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

