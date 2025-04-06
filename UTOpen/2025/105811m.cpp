#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const ll MN = 100005;
const ll MX = 100005;
const ll MOD = 1e9 + 7;

const ll SQRT = 350;
ll A[MN];
ll ways[2][MX];

ll binpow(ll a, ll x, const ll mod) {
    ll ret = 1;
    for (; x > 0; x >>= 1) {
        if (x & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll N;
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    ways[0][0] = 1;
    for (ll i=0; i<N && i<SQRT; ++i) {
        for (int j=0; j<=(i+1)*(i+1) && j<MX; ++j) {
            ways[(i^1)&1][j] = (ways[i&1][j] + (j >= A[i] ? ways[i&1][j - A[i]] : 0)) % MOD;
        }
    }

    const int i = min(N, SQRT);
    const ll p = max(0LL, N - SQRT);
    ll ans = 0;
    for (int j=0; j<MX; ++j) {
        ans += ways[i & 1][j] * binpow(2, p, MOD) % MOD;
    }
    ans %= MOD;
    cout << ans << '\n';
}
