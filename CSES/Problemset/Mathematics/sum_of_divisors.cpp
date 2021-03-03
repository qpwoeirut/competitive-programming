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
        ll start = i*(i-1), finish = (N / i) * i;
        ans = (ans + finish - start) % MOD;
        //cerr << i << ' ' << ans << endl;

        ll terms = (N / i) - i;
        start = i+1;
        finish = N / i;
        ll x = start + finish;
        //cerr << "s,f: " << start << ' ' << finish << endl;
        //cerr << "t,x: " << terms << ' ' << x << endl;

        if (x & 1) {
            terms >>= 1;
        } else {
            x >>= 1;
        }
        terms %= MOD;
        x %= MOD;
        ans = (ans + terms * x) % MOD;
        //cerr << i << ' ' << ans << endl;
    }

    cout << ans << endl;
}

