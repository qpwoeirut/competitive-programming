//cses_exponentiation_ii.cpp created at 12/19/20 14:46:12

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

int N;

ll binpow(ll x, ll p, const ll mod) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        ll p = binpow(b, c, MOD - 1);
        cout << binpow(a, p, MOD) << endl;
    }
}

