#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 100001;
const ll MOD = 1e9 + 7;

int N, K;
int A[MN];

ll ways[MN];

ll fact[MN<<1], inv_fact[MN<<1];
ll choose(int n, int k) {
    return (((fact[n] * inv_fact[k]) % MOD) * inv_fact[n-k]) % MOD;
}

ll binpow(ll a, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret = (ret * a) % MOD;
        p >>= 1;
        a = (a * a) % MOD;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;

    fact[0] = inv_fact[0] = 1;
    for (int i=1; i<MN*2; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
        inv_fact[i] = binpow(fact[i], MOD-2);
    }

    int max_a = 0;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        max_a = max(max_a, A[i]);
    }

    for (int k=1; k<=K; ++k) {
        ways[k] = 1;
        for (int i=0; i<N; ++i) {
            ways[k] = (ways[k] * choose(A[i] + k - 1, k - 1)) % MOD;
        }
        for (int i=1; i<k; ++i) {
            ways[k] -= ways[i] * choose(k, k-i);
            ways[k] %= MOD;
        }
    }
    //for (int i=0; i<=K; ++i) { cerr << ways[i] << ' '; } cerr << endl;
    
    if (ways[K] < 0) ways[K] += MOD;
    cout << ways[K] << '\n';
}
