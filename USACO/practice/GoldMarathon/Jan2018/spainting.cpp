#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 1000005;
const ll MOD = 1e9 + 7;

ll N, M, K;
ll dp[MN];
ll psum[MN];

ll binpow(ll a, ll x) {
    ll ret = 1;
    while (x) {
        if (x & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        x >>= 1;
    }
    return ret;
}

int main() {
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;

    for (int i=0; i<K; ++i) {
        dp[i] = binpow(M, i);
        psum[i] = (dp[i] + (i ? psum[i-1] : 0)) % MOD;
    }
    for (int i=K; i<=N; ++i) {
        dp[i] = ((((psum[i-1] - psum[i-K]) * (M-1)) % MOD) + MOD) % MOD;
        psum[i] = (psum[i-1] + dp[i]) % MOD;
    }

    //for (int i=0; i<=N; ++i) { cerr << dp[i] << ' '; } cerr << endl;
    //for (int i=0; i<=N; ++i) { cerr << psum[i] << ' '; } cerr << endl;

    ll total = binpow(M, N);
    ll ans = (total - dp[N] + MOD) % MOD;
    cout << ans << endl;
}
