//cses_exponentiation.cpp created at 12/19/20 14:40:44

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

int N;

ll binpow(ll x, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        ll a, b;
        cin >> a >> b;
        cout << binpow(a, b) << '\n';
    }
}
    
