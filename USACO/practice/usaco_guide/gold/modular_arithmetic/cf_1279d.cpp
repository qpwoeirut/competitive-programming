//cf_1279d.cpp created at 12/19/20 15:06:46

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 1000005;
const ll MOD = 998244353;

ll binpow(ll x, ll p, const ll mod) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return ret;
}

ll N;
vector<int> A[MN];
ll ct[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        int K;
        cin >> K;
        A[i] = vector<int>(K);
        for (int j=0; j<K; ++j) {
            cin >> A[i][j];
            ++ct[A[i][j]];
        }
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ll total = 0;
        for (const int x: A[i]) {
            total += ct[x];
        }
        const ll K = A[i].size();
        ans = (ans + total * binpow(N*N*K % MOD, MOD-2, MOD)) % MOD;
    }

    cout << ans << endl;
}

