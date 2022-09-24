//watering_well.cpp created at 09/11/22 01:22:06
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

using ll = long long;
using pll = pair<ll,ll>;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

void setIO(const string& filename = "watering_well") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

constexpr ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 500000;

inline const ll square(const ll x) {
    return x * x;
}

ll N, Q;
pll A[MN];

// stupid brute sol
void solve(int testcase) {
    cin >> N;

    ll ans = 0;
    for (int i=0; i<N; ++i) cin >> A[i].fi >> A[i].se;
    cin >> Q;
    for (int q=0; q<Q; ++q) {
        ll x, y;
        cin >> x >> y;

        for (int i=0; i<N; ++i) {
            ans += (square(x - A[i].fi) + square(y - A[i].se)) % MOD;
        }
        ans %= MOD;
    }

    cout << "Case #" << testcase << ": " << ans << '\n';
}

int main() {
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cerr << test_case << endl;
        solve(test_case);
    }

    return 0;
}
