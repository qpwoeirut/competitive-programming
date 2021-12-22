#include <bits/stdc++.h>

using namespace std;

const int MN = 503;
const int MOD = 1e9 + 7;

struct mint {
    long long val;
    mint() {
        val = 0;
    }
    mint(const int x) {
        val = x;
        if (val >= MOD) val -= MOD;
    }
    mint operator+(const mint& o) const {
        return mint(val + o.val);
    }
    mint operator+=(const mint& o) {
        val += o.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    mint operator*(const long long x) const {
        return mint((val * x) % MOD);
    }
    mint operator=(const int x) {
        val = x;
        return *this;
    }
};

int N, X;
mint dp[2][MN][MN][2];
mint ct[2][MN][MN][2];
mint ldp[MN][MN][2], rdp[MN][MN][2];
mint lct[MN][MN][2], rct[MN][MN][2];

int main() {
    cin >> N >> X;

    for (int i=1; i<=X; ++i) {
        ct[1][i][N+1][0] = 1;
    }
    for (int i=N; i>X; --i) {
        ct[1][0][i][1] = 1;
    }
    for (int n=2; n<=N; ++n) {
        for (int l=0; l<=X; ++l) {
            for (int r=N+1; r>X; --r) {
                for (int k=0; k<2; ++k) {
                    ldp[l+1][r][k] = ldp[l][r][k] + dp[(n&1)^1][l][r][k];
                    rdp[l][r-1][k] = rdp[l][r][k] + dp[(n&1)^1][l][r][k];
                    lct[l+1][r][k] = lct[l][r][k] + ct[(n&1)^1][l][r][k];
                    rct[l][r-1][k] = rct[l][r][k] + ct[(n&1)^1][l][r][k];
                }
            }
        }
        for (int l=0; l<=X; ++l) {
            for (int r=N+1; r>X; --r) {
                dp[n&1][l][r][0] = dp[(n&1)^1][l][r][0] * max(0, N - (r - l - 1) - (n - 1));
                dp[n&1][l][r][1] = dp[(n&1)^1][l][r][1] * max(0, N - (r - l - 1) - (n - 1));
                ct[n&1][l][r][0] = ct[(n&1)^1][l][r][0] * max(0, N - (r - l - 1) - (n - 1));
                ct[n&1][l][r][1] = ct[(n&1)^1][l][r][1] * max(0, N - (r - l - 1) - (n - 1));
                // N total numbers, can't choose in the range (l, r), n-1 already used

                dp[n&1][l][r][0] += ldp[l][r][0] + ldp[l][r][1] + lct[l][r][1];
                ct[n&1][l][r][0] += lct[l][r][0] + lct[l][r][1];

                dp[n&1][l][r][1] += rdp[l][r][0] + rdp[l][r][1];
                ct[n&1][l][r][1] += rct[l][r][0] + rct[l][r][1];
            }
        }
    }
    /*
    for (int n=1; n<=N; ++n) {
        for (int l=0; l<=X; ++l) {
            for (int r=X+1; r<=N+1; ++r) {
                //cerr << "dp: " << n << ' ' << l << ' ' << r << ": " << dp[n][l][r][0].val << ' ' << dp[n][l][r][1].val << endl;
                //cerr << "ct: " << n << ' ' << l << ' ' << r << ": " << ct[n][l][r][0].val << ' ' << ct[n][l][r][1].val << endl;
            }
        }
    }
    */

    cout << (dp[N&1][X][X+1][0] + dp[N&1][X][X+1][1]).val << endl;
}

