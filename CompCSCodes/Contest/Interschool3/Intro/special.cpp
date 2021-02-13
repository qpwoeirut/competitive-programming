//special.cpp created at 02/03/21 18:51:12

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {
    freopen("special.in", "r", stdin);
    freopen("special.out", "w", stdout);
    ll N;
    cin >> N;

    ll p[3] = {2, 3, 11};
    ll ans[3] = {0, 0, 0};
    for (int i=0; i<3; ++i) {
        while (N > 1 && ((N % p[i]) == 0)) {
            N /= p[i];
            ++ans[i];
        }
    }

    cout << ans[0] << ' ' << ans[1] << ' ' << ans[2] << endl;
}

