#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 100005;
const ll MOD = 1e9 + 7;

ll binpow(ll a, ll n) {
    ll ret = 1;
    for (; n>0; n>>=1) {
        if (n & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
    }
    return ret;
}

int N, M;
bitset<MN> A[20];
int hardness[MN];

int brute(bitset<MN>& used, const int h_sum) {
    for (int i=0; i<N; ++i) {
        hardness[i] = 0;
        for (int j=0; j<M; ++j) {
            hardness[i] = (hardness[i] << 1) | A[j][i];
        }
    }
    int ret = 1;
    for (int i=0; i<N; ++i) {
        if (!used[i] && (h_sum & hardness[i]) == h_sum) {
            used[i] = true;
            ret += brute(used, h_sum | hardness[i]);
            used[i] = false;
        }
    }
    return ret;
}

ll perms[MN];
int group[MN];
ll dp[MN], dp_h[1 << 20];

int solve() {
    for (int i=0; i<N; ++i) {
        hardness[i] = 0;
        for (int j=0; j<M; ++j) {
            hardness[i] = (hardness[i] << 1) | A[j][i];
        }
    }
    sort(hardness, hardness+N);

    fill(dp, dp+N, 0);
    fill(dp_h, dp_h+(1 << M), 0);

    perms[0] = 0;
    for (int i=1; i<=N; ++i) {
        perms[i] = (perms[i-1] * i + i) % MOD;
    }

    int G = 1;
    for (int i=1; i<N; ++i) {
        if (hardness[i-1] != hardness[i]) {
            group[G++] = i;
        }
    }
    group[G] = N;

    for (int i=0; i<G; ++i) {
        const int gsize = group[i+1] - group[i];

        ll prev_groups = 1 + dp_h[0];
        const int h = hardness[group[i]];
        for (int mask=h; mask>0; mask=(mask - 1) & h) prev_groups += dp_h[mask];
        prev_groups %= MOD;

        dp[i] = (perms[gsize] * prev_groups) % MOD;
        dp_h[h] = dp[i];
        //cerr << i << ' ' << dp[i] << ' ' << gsize << ' ' << perms[gsize] << ' ' << prev_groups << endl;
    }

    ll ans = 0;
    for (int i=0; i<G; ++i) ans += dp[i];
    return ans % MOD;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=7; ++N) {
        for (M=1; M<=15; ++M) {
            cout << N << ' ' << M << endl;
            for (int t=0; t<100000; ++t) {
                for (int m=0; m<M; ++m) {
                    for (int n=0; n<N; ++n) {
                        A[m][n] = rng() & 1;
                    }
                }

                bitset<MN> b;
                const int bans = brute(b, 0) - 1;
                const int sans = solve();
                if (bans != sans) {
                    cout << N << ' ' << M << '\n';
                    for (int i=0; i<M; ++i) {
                        for (int j=0; j<N; ++j) {
                            cout << "EH"[A[i][j]];
                        }
                        cout << '\n';
                    }
                    cout << bans << ' ' << sans << endl;
                    assert(0);
                }
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    //test(); return 0;

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        string S;
        cin >> S;
        for (int j=0; j<N; ++j) {
            A[i][j] = S[j] == 'H';
        }
    }
    
    cout << solve() << '\n';
}
/*
1 1
H
1

3 1
HHH
15
*/
