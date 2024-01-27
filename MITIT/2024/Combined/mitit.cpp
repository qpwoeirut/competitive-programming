#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 200005;

ll T[MN], A[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M;
    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> T[i] >> A[i];
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ll x = (M - T[i] + A[i] - 1) / A[i];
        ans = max(ans, x);
    }

    cout << ans + 1 << '\n';
}
