//bovine_genetics_s2.cpp created at 01/24/21 10:46:34
// submitted for subtask 2 at 12:28

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 205;
const ll MOD = 1e9 + 7;

string S;
ll dp[MN][4];
ll ways[MN][MN][4][4];

string CHARS = "ACGT";

bool ok(const int idx, const int cidx) {
    return S[idx] == CHARS[cidx] || S[idx] == '?';
}

void add(ll& a, const ll b) {
    a += b;
    if (a >= MOD) a -= MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> S;
    const int N = S.size();
    assert(N < MN); // only worried about subtask 1-2 for now

    for (int i=0; i<N; ++i) {
        for (int k=0; k<4; ++k) {
            if (!ok(i, k)) continue;
            for (int j=i; j<N; ++j) {
                for (int l=0; l<4; ++l) {
                    if (!ok(j, l)) continue;
                    if (i == j) {
                        if (k == l) {
                            ++ways[i][j][k][l];
                        }
                    } else {
                        for (int p=0; p<4; ++p) {
                            if (p == l) continue;
                            add(ways[i][j][k][l], ways[i][j-1][k][p]);
                        }
                    }
                }
            }
        }
    }
    //for (int i=0; i<N; ++i) {
    //    for (int j=0; j<N; ++j) {
    //        for (int k=0; k<4; ++k) {
    //            for (int l=0; l<4; ++l) {
    //                if (ways[i][j][k][l] == 0) continue;
    //                cerr << i << ' ' << j << ' ' << k << ' ' << l << ": " << ways[i][j][k][l] << endl;
    //            }
    //        }
    //    }
    //}

    for (int k=0; k<4; ++k) {
        dp[0][k] = 1;
    }
    for (int i=1; i<=N; ++i) {
        for (int j=0; j<i; ++j) {
            for (int k=0; k<4; ++k) {
                for (int l=0; l<4; ++l) {
                    add(dp[i][k], (dp[j][l] * ways[j][i-1][k][l]) % MOD);
                }
            }
        }
    }
    //for (int i=0; i<=N; ++i) { for (int j=0; j<4; ++j) { cerr << dp[i][j] << ' '; } cerr << endl; }

    ll ans = 0;
    for (int k=0; k<4; ++k) {
        add(ans, dp[N][k]);
    }
    cout << ans << endl;
}

/*
?
GAT?GTT
A?A
*/
