//eggs.cpp created at 02/04/21 20:24:07
// mfw i spend over an hour on bronze p1, cant solve, and then solve p2 in 3 minutes

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;

ll N, K;
ll Q[MN], W[MN];

int main() {
    freopen("eggs.in", "r", stdin);
    freopen("eggs.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> Q[i] >> W[i];
    }

    ll ans = 0;
    int slow = 0;
    ll quality = 0, weight = 0;
    for (int i=0; i<N; ++i) {
        quality += Q[i];
        weight += W[i];
        while (weight > K) {
            quality -= Q[slow];
            weight -= W[slow];
            ++slow;
        }
        ans = max(ans, quality);
    }

    cout << ans << endl;
}
