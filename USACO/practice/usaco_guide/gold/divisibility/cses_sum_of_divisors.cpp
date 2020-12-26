//cses_sum_of_divisors.cpp created at 12/19/20 13:51:33

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

ll N;

int main() {
    cin >> N;

    ll ans = 0;
    ll i;
    for (i=1; i*i<=N; ++i) {
        ans = (ans + (N / i) * i) % MOD;
    }
    ll terms = N - 1;
    ll x = N + 2;

    if (x & 1) {
        terms >>= 1;
    } else {
        x >>= 1;
    }
    terms %= MOD;
    x %= MOD;
    ans = (ans + terms * x) % MOD;

    cout << ans << endl;
}

