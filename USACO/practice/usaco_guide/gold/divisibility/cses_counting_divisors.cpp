//cses_counting_divisors.cpp created at 12/19/20 11:56:06

#include <bits/stdc++.h>

using namespace std;

const int MX = 1000005;

int N;
int pf[MX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    pf[1] = 1;
    for (int i=2; i<MX; ++i) {
        if (pf[i] != 0) continue;
        for (int j=i; j<MX; j+=i) {
            pf[j] = i;
        }
    }

    cin >> N;
    for (int i=0; i<N; ++i) {
        int x;
        cin >> x;

        int ans = 1;
        while (x > 1) {
            const int p = pf[x];
            int ct = 0;
            while (x % p == 0) {
                x /= p;
                ++ct;
            }
            ans *= ct + 1;
        }

        cout << ans << endl;
    }
}

