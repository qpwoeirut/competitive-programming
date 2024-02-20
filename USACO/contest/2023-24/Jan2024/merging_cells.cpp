#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 5003;
const int MOD = 1e9 + 7;

ll binpow(ll x, ll p) {
    ll ret = 1;
    for (; p > 0; p >>= 1) {
        if (p & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
    }
    return ret;
}

int N;
int A[MN];

int sum[MN];
ll dp[MN][MN];
ll fact[MN];
ll invf[MN];

int perm(int n, int k) {
    return (fact[n] * invf[n - k]) % MOD;
}

int ans[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    fact[0] = 1;
    invf[0] = 1;
    for (int i=1; i<MN; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invf[i] = binpow(fact[i], MOD - 2);
    }

    sum[0] = 0;

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        sum[i + 1] = sum[i] + A[i];
    }

    for (int i=0; i<N; ++i) {
        for (int a=0; a<N; ++a) {
            for (int b=0; b<N; ++b) {
                dp[a][b] = a == i && b == i;
            }
        }
        for (int len=2; len<=N; ++len) {
            for (int a=0; a<=N - len; ++a) {
                const int b = a + len - 1;
                if (i < a || b < i) continue;

                for (int x=a+1; x<=i; ++x) {
                    dp[a][b] += (sum[x] - sum[a] <= sum[b + 1] - sum[x]) ? 
                        (dp[x][b] * perm(b - a - 1, x - a - 1)) % MOD : 0;
                }
                for (int x=i; x<b; ++x) {
                    dp[a][b] += (sum[x + 1] - sum[a] > sum[b + 1] - sum[x + 1]) ? 
                        (dp[a][x] * perm(b - a - 1, b - x - 1)) % MOD : 0;
                    //cerr << a << ' ' << b << ' ' << x << ' ' << dp[a][x] << ' ' << perm(b - a - 1, b - x - 1) << endl;
                }
                dp[a][b] %= MOD;

                //cerr << i << ' ' << a << ' ' << b << ' ' << dp[a][b] << endl;
            }
        }

        ans[i] = (dp[0][N-1] * invf[N - 1]) % MOD;
    }

    for (int i=0; i<N; ++i) {
        cout << ans[i] << '\n';
    }
}
/*
4
5 1 1 1
*/
