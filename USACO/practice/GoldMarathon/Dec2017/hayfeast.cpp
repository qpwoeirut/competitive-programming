#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;

ll N, M;
ll A[MN], B[MN];

int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
    }

    ll ans = 1e18;
    int slow = 0;
    multiset<ll> spice;
    ll cur = 0;
    for (int fast=0; fast<N; ++fast) {
        cur += A[fast];
        spice.insert(B[fast]);
        while (cur - A[slow] >= M) {
            cur -= A[slow];
            spice.erase(spice.find(B[slow]));
            ++slow;
        }

        if (cur >= M) {
            ans = min(ans, *spice.rbegin());
        }
    }

    cout << ans << endl;
}
