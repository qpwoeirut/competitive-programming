//1485a.cpp created at 02/27/21 11:40:07

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll cost(ll a, ll b) {
    if (b == 1) return 1e9;
    ll x = 0;
    while (a > 0) {
        ++x;
        a /= b;
    }
    return x;
}

void solve() {
    ll a, b;
    cin >> a >> b;

    ll ans = 1e9;
    for (int i=0; i<32; ++i) {
        ans = min(ans, i + cost(a, b+i));
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    for (int t=1; t<=T; ++t) solve();
}

