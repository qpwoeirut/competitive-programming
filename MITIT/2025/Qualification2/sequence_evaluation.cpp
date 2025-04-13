//sequence_evaluation.cpp created at 04/12/25 16:52:30
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

const int MN = 100001;

ll K;
ll A[MN];

struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(-1ULL / b) {}
	ull reduce(ull a) {
		ull q = (ull)((__uint128_t(m) * a) >> 64), r = a - q * b;
		return r - (r >= b) * b;
	}
};

ll inv[MN];
void solve(int testcase) {
    ll P, X;
    cin >> K >> P >> X;

    for (int i=0; i<MN; ++i) {
        inv[i] = binpow(i, P - 2, P);
    }
    FastMod mod(P);
    
    A[1] = 1;
    for (int i=2; i<=P - K; ++i) {
        A[i] = 0;
        for (int j=1; j<i; ++j) {
            A[i] += mod.reduce(A[j] * inv[i - j]);
        }
        A[i] = mod.reduce(mod.reduce(A[i]) * X);
    }

    cout << A[P - K] << '\n';
}

int main() {
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
