#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        int a, b, n;
        cin >> n >> a >> b;

        int g = gcd(a, b);
        cout << (n % g ? "NO" : "YES") << '\n';
    }
}
