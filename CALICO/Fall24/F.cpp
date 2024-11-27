// CALICO 2024: Problem F

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define f first
#define s second

vector<int> pfs(1, 0);

set<int> primeFactors(int n) {
    set<int> factors;

    // Check for divisibility by 2
    while (n % 2 == 0) {
        factors.insert(2);
        n /= 2;
    }

    // Check for divisibility by odd numbers starting from 3
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.insert(i);
            n /= i;
        }
    }

    // If n is a prime number greater than 2
    if (n > 2) {
        factors.insert(n);
    }

    return factors;
}

int phi(int n) {
    int ans = n;
    for (auto x : primeFactors(n)) {
        ans /= x, ans *= x - 1;
    }
    return ans;
}

const int PRE = 1000;
const int MAX = 48623 + 8734 + 1;
const int OFF = MAX - PRE + 1;
int hc[PRE][MAX + 1];

void solve() {
    int n;
    cin >> n;
    int i = --lower_bound(pfs.begin(), pfs.end(), n) - pfs.begin();
    n -= pfs[i];

    i += 2;
    const int idx = i - OFF;
    int x = 0;
    if (0 <= idx) {
        assert(idx < PRE);
        x = hc[idx][n - 1];
    } else {
        for (int k = 0; k < n; k++) {
            x++;
            while (gcd(x, i) != 1) {
                x++;
            }
        }
    }
    cout << x << ' ' << i - x << '\n';
}

void gen() {
    for (int di=OFF; di<MAX; ++di) {
        int ct = 0;
        for (int x=1; x<di; ++x) {
            if (gcd(x, di) == 1) hc[di - OFF][ct++] = x;
        }
    }
}

int32_t main() {
    gen();
    for (int i = 2; pfs.back() < 1e9 + 10; i++) {
        pfs.push_back(pfs.back() + phi(i));
    }
    // for (int i = 0; i < 100; i++) cout << pfs[i] << ' ';
    // cout << '\n';
    int t = 1;
    cin >> t;
    while (t--) solve();
}
/*
24
1
10000
100000000
200000000
300000000
400000000
500000000
600000000
700000000
800000000
900000000
999000000
999900000
999910000
999920000
999930000
999940000
999950000
999960000
999970000
999980000
999990000
999999000
1000000000
*/
