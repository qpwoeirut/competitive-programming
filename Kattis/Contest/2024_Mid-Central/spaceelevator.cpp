#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pll=pair<ll,ll>;

const int MN = 100005;
const ll INF = 1e18;

ll N, H0;
pll A[MN];

ll pmin[MN], pmax[MN];
ll smin[MN], smax[MN];

ll cost() {
    sort(A, A+N);

    ll mx = -INF, mn = INF;
    for (int i=0; i<N; ++i) {
        mx = max(mx, max(A[i].first, A[i].second));
        mn = min(mn, min(A[i].first, A[i].second));
    }

    pmin[0] = mx;
    pmax[0] = mn;
    for (int i=1; i<=N; ++i) {
        pmin[i] = min(pmin[i-1], A[i-1].second);
        pmax[i] = max(pmax[i-1], A[i-1].second);
    }

    smin[N] = mx;
    smax[N] = mn;
    for (int i=N-1; i>=0; --i) {
        smin[i] = min(smin[i+1], A[i].second);
        smax[i] = max(smax[i+1], A[i].second);
    }

    int base_idx = lower_bound(A, A+N, pll(H0, INF)) - A - 1;
    ll ans = INF;
    for (int i=0; i<N; ++i) {
        int bi = max(i, base_idx);
        ll lo = min(A[0].first, pmin[bi + 1]);
        ll hi = max(A[N-1].first, pmax[N]);
        ll fin = smin[bi + 1];

        ans = min(ans, abs(A[bi].first - H0) + abs(lo - A[bi].first) + abs(hi - lo) + abs(fin - hi));
        cerr << i << ' ' << H0 << ' ' << A[bi].first << ' ' << lo << ' ' << hi << ' ' << fin << endl;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> H0;
    for (int i=0; i<N; ++i) {
        cin >> A[i].first >> A[i].second;
    }

    ll ans = cost();
    for (int i=0; i<N; ++i) {
        A[i].first *= -1;
        A[i].second *= -1;
    }
    H0 = -H0;
    ans = min(ans, cost());

    cout << ans << endl;
}

/*
1 0
0 1

3 10
1 5
3 10
6 0

3 5
6 1
3 8
7 10

4 5
6 1
3 8
7 100
103 95
*/
