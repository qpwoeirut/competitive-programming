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
            if (!ok(i, j)) continue;
            if (good(2*i, 'x') && good(2*i+1, '-')) {
                //cerr << "strike" << endl;

                for (int k=0; k<MS; ++k) {
                    if (dp[i][j][STRIKE][k] == 0) continue;
                    for (int l=0; l<MS; ++l) {
                        const int score = j + 10 + k + l;
                        dp[i+1][score][k][l] += dp[i][j][STRIKE][k];
                    }
                }
            }
            for (int a=0; a<10; ++a) {
                if (!good(2 * i, '0' + a)) continue;

                if (good(2*i + 1, '/')) {
                    //cerr << "spare a=" << a << endl;

                    for (int k=0; k<MS; ++k) {
                        const int score = j + 10 + k;
                        if (dp[i][j][a][10-a] == 0 || !ok(i+1, score)) continue;
                        for (int l=0; l<MS; ++l) {
                            dp[i+1][score][k][l] += dp[i][j][a][10-a];
                        }
                    }
                }
                for (int b=0; a+b<10; ++b) {
                    if (good(2*i + 1, '0' + b)) {
                        //cerr << "a,b=" << a << "," << b << endl;
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

    //for (int i=0; i<N; ++i) { const int j = A[i]; for (int k=0; k<MS; ++k) {
    //for (int l=0; l<MS; ++l) { if (dp[i][j][k][l]) { cerr << i << ' ' << j << ' ' << k << ' ' << l << " = " << dp[i][j][k][l] << endl; } } } }

    ll ans = 0;
    const int i = N-1;
    for (int j=0; j<MX; ++j) {
        if (!ok(i, j)) continue;
        //cerr << i << ' ' << j << endl;
        if (good(2*i, 'x') && good(2*i + 1, 'x') && good(2*i + 2, 'x')) {
            const int score = j + 30;
            //cerr << "xxx " << score << ' ' << ok(N, score) << endl;
            if (ok(N, score)) ans += dp[i][j][STRIKE][STRIKE];
        }

        for (int a=0; a<10; ++a) {
            if (good(2*i, 'x')) {
                if (good(2*i + 1, 'x') && good(2*i + 2, '0' + a)) {
                    const int score = j + 20 + a;
                    //cerr << "xx" << a << " " << score << ' ' << ok(N, score) << endl;
                    if (ok(N, score)) ans += dp[i][j][STRIKE][STRIKE];
                }

                if (good(2*i + 1, '0' + a)) {
                    if (good(2*i + 2, '/')) {
                        const int score = j + 20;
                        //cerr << "x" << a << "/ " << score << ' ' << ok(N, score) << endl;
                        if (ok(N, score)) ans += dp[i][j][STRIKE][a];
                    }

                    for (int b=0; a+b<10; ++b) {
                        if (good(2*i + 2, '0' + b)) {
                            const int score = j + 10 + a + b;
                            //cerr << "x" << a << b << ' ' << score << ' ' << ok(N, score) << endl;
                            if (ok(N, score)) ans += dp[i][j][STRIKE][a];
                        }
                    }
                }
            }

            if (good(2*i, '0' + a)) {
                if (good(2*i + 1, '/')) {
                    if (good(2*i + 2, 'x')) {
                        const int score = j + 20;
                        //cerr << a << "/x" << ' ' << score << ' ' << ok(N, score) << endl;
                        if (ok(N, score)) ans += dp[i][j][a][10-a];
                    }
                    for (int b=0; a+b<10; ++b) {
                        if (good(2*i + 2, '0' + b)) {
                            const int score = j + 10 + b;
                            //cerr << a << "/" << b << ' ' << score << ' ' << ok(N, score) << endl;
                            if (ok(N, score)) ans += dp[i][j][a][10-a];
                        }
                    }
                }
                for (int b=0; a+b<10; ++b) {
                    if (good(2*i + 1, '0' + b) && good(2*i + 2, '-')) {
                        const int score = j + a + b;
                        //cerr << a << b << "- " << score << ' ' << ok(N, score) << endl;
                        if (ok(N, score)) ans += dp[i][j][a][b];
                    }
                }
            }
        }
    }
    return ans;
}

#define fi first
#define se second

typedef pair<int,int> pii;
pii B[MN];
int sc[MN];
bool check(const string& s) {
    //cerr << s << endl;
    for (int i=0; i<s.size(); i+=2) {
        const int fr = i >> 1;
        if (fr == N-1) break;

        if (s[i] == 'x') B[fr] = pii(10, 0);
        else {
            B[fr] = pii(s[i] - '0', s[i+1] == '/' ? 10 - (s[i] - '0') : s[i+1] - '0');
        }
    }
    const int idx = 2*(N-1);
    const int fr = N-1;
    if (s[idx] == 'x') B[fr].fi = 10;
    else B[fr].fi = s[idx] - '0';

    if (s[idx+1] == 'x') B[fr].se = 10;
    else if (s[idx+1] == '/') B[fr].se = 10 - B[fr].fi;
    else B[fr].se = s[idx+1] - '0';

    for (int i=0; i<N-1; ++i) {
        sc[i] = i ? sc[i-1] : 0;

        sc[i] += B[i].fi + B[i].se;
        if (B[i].fi + B[i].se == 10) {
            sc[i] += B[i+1].fi;
        }
        if (B[i].fi == 10) {
            if (B[i+1].fi == 10 && i+2 < N) sc[i] += B[i+2].fi;
            else sc[i] += B[i+1].se;
        }
    }

    sc[N-1] = sc[N-2];
    if (s[idx] == 'x') {
        sc[N-1] += 10;
        if (s[idx+1] == 'x') {
            sc[N-1] += 10;
        } else {
            sc[N-1] += s[idx+1] - '0';
        }
        if (s[idx+2] == 'x') {
            sc[N-1] += 10;
        } else if (s[idx+2] == '/') {
            sc[N-1] += 10 - (s[idx+1] - '0');
        } else {
            sc[N-1] += s[idx+2] - '0';
        }
    } else {
        if (s[idx+1] == '/') {
            sc[N-1] += 10;
            if (s[idx+2] == 'x') sc[N-1] += 10;
            else sc[N-1] += s[idx+2] - '0';
        } else {
            sc[N-1] += s[idx] - '0' + s[idx+1] - '0';
        }
    }

    for (int i=0; i<N; ++i) {
        //cerr << sc[i] << ' ' << A[i+1] << endl;
        if (sc[i] != A[i+1] && A[i+1] != -1) return false;
    }
    return true;
}

bool valid(const string& s) {
    for (int i=0; i+1<s.size(); ++i) {
        if ((s[i] == 'x' || s[i] == '/' || s[i] == '-') && s[i+1] == '/') return false;
        if (s[i] == '-' && s[i+1] == '/') return false;
        if (s[i] == '-' && s[i+1] == '-') return false;
    }
    for (int i=0; i+1<s.size(); i+=2) {
        if (s[i] == '/') return false;
        if (isdigit(s[i]) && isdigit(s[i+1]) && s[i] - '0' + s[i+1] - '0' >= 10) return false;
    }
    for (int i=0; i+4<s.size(); i+=2) {
        if (s[i+1] == 'x') return false;
        if (s[i] == 'x' && s[i+1] != '-') return false;
        if (s[i] == '-') return false;
        if (isdigit(s[i]) && (s[i+1] == '-' || s[i+1] == 'x')) return false;
    }

    const int i = s.size() - 3;
    if (s[i] == '/' || s[i] == '-' || s[i+1] == '-') return false;
    if (s[i] != 'x' && s[i+1] == 'x') return false;
    if (isdigit(s[i]) && isdigit(s[i+1]) && s[i+2] != '-') return false;
    if (s[i] == 'x' && (s[i+1] == '-' || s[i+2] == '-')) return false;
    if (isdigit(s[i+1]) && s[i+2] == 'x') return false;
    if (isdigit(s[i+1]) && isdigit(s[i+2]) && s[i+1] - '0' + s[i+2] - '0' >= 10) return false;
    if ((s[i+1] == 'x' || s[i+1] == '/') && s[i+2] == '-') return false;

    //cerr << s << endl;
    return true;
}

ll bans = 0;
void gen(const int idx) {
    if (idx == S.size()) {
        if (valid(S)) bans += check(S);
        return;
    }
    if (S[idx] == '?') {
        if (idx+4 >= S.size() || ((idx & 1) == 0)) {
            S[idx] = 'x';
            gen(idx+1);
        }
        if (idx > 0 && isdigit(S[idx-1])) {
            S[idx] = '/';
            gen(idx+1);
        }
        if (idx > 0 && (S[idx-1] == 'x' || (idx+1 == S.size() && isdigit(S[idx-1])))) {
            S[idx] = '-';
            gen(idx+1);
        }
        if (idx == 0 || idx+4 >= S.size() || S[idx-1] != 'x') {
            for (char a='0'; a<='9'; ++a) {
                if (idx+4 < S.size() && (idx & 1) && (!isdigit(S[idx-1]) || S[idx-1] - '0' + a - '0' >= 10)) continue;
                S[idx] = a;
                gen(idx+1);
            }
        }
        S[idx] = '?';
    } else gen(idx+1);
}

ll brute() {
    bans = 0;
    gen(0);
    return bans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int test_cases;
    cin >> test_cases;
    for (int t=1; t<=test_cases; ++t) {
        cin >> N;
        cin >> S;
        int x = 0;
        for (int i=1; i<=N; ++i) cin >> A[i];
        for (char c: S) if (c == '?') ++x;
        if (x <= 6) cout << brute() << endl;
        else cout << solve() << endl;
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

