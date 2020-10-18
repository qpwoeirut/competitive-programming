#include <bits/stdc++.h>

using namespace std;

const int MX = 1e9 + 1000;

bool prime[MX];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("primes.out", "w", stdout);

    for (int i=3; i<MX; i+=2) {
        prime[i] = true;
    }
    prime[2] = true;
    cout << 2 << '\n';

    for (int i=3; i<MX; i+=2) {
        if ((i & ((1 << 17) - 1)) == (1 << 16)) {
            cerr << i << ' ';
        }
        if (!prime[i]) continue;
        for (int j=i+i; j<MX; j+=i) {
            prime[j] = false;
        }
        cout << i << '\n';
    }
}
