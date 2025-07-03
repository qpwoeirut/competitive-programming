#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    ll n, x;
    cin >> n >> x;

    const ll g = gcd(n, x);
    cout << n - (n / g) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--> 0) {
        solve();
    }
}
