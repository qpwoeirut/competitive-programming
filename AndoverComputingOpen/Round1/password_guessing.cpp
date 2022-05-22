#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll MOD = 1e9 + 7;

ll N, M, K, T;

ll binpow(ll a, ll b) {
    a %= MOD;
    ll ret = 1;
    while (b > 0) {
        if (b & 1) ret = (ret * a) % MOD;
        b >>= 1;
        a = (a * a) % MOD;
    }
    return ret;
}

int main() {
    cin >> N >> M >> K >> T;

    const ll inv_n = binpow(N, MOD - 2);
    const ll inv_m = binpow(M, MOD - 2);
    const ll inv_nm = (inv_n * inv_m) % MOD;

    assert((N * inv_n) % MOD == 1);
    assert((M * inv_m) % MOD == 1);

    ll p0 = 1, pn = 0;
    for (int t=1; t<T; ++t) {
        ll p0_ = (p0 * inv_m + pn * inv_nm) % MOD;

        ll x = ((M - 1) * (N - 1)) % MOD;
        ll pn_ = (pn * inv_m + pn * ((inv_nm * x) % MOD) + p0 * ((inv_m * (M - 1)) % MOD)) % MOD;

        p0 = p0_;
        pn = pn_;

        cerr << p0 << ' ' << pn << endl;
        assert((p0 + pn) % MOD == 1);
    }

    pn = (pn * inv_n) % MOD;
    ll ans = (p0 + (pn * (K - 1))) % MOD;
    if (ans < 0) ans += MOD;
    cout << ans << '\n';
}
