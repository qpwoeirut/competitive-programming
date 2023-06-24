//binaria.cpp created at 06/15/23 20:19:13

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 1001001;
const int MOD = 1e6 + 3;

ll binpow(ll x, ll p) {
    if (p == 0) return 1;
    x %= MOD;
    ll y = (p & 1) ? x : 1;
    return (y * binpow((x*x) % MOD, p >> 1)) % MOD;
}

int N, K;
int A[MN];
int B[MN];

ll fact[MN];

void resolve(int i, int j) {
    assert(B[i] == -1 || B[j] == -1 || B[i] == B[j]);
    if (B[i] == -1) B[i] = B[j];
    if (B[j] == -1) B[j] = B[i];
}

ll choose(ll n, ll k) {
    if (n < k) return 0;

    ll denom = binpow((fact[k] * fact[n-k]) % MOD, MOD - 2);
    return (fact[n] * denom) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    fact[0] = 1;
    for (int i=1; i<MN; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
    }

    cin >> N >> K;
    const int M = N - K + 1;
    for (int i=0; i<M; ++i) {
        cin >> A[i];
    }

    fill(B, B+N, -1);

    for (int i=0; i+1<M; ++i) {
        if (A[i] == A[i+1]) {
            resolve(i, i+K);
        } else if (A[i] + 1 == A[i+1]) {
            B[i] = 0;
            B[i+K] = 1;
        } else if (A[i] - 1 == A[i+1]) {
            B[i] = 1;
            B[i+K] = 0;
        } else assert(0);
    }

    for (int i=M-2; i>=0; --i) {
        if (A[i] == A[i+1]) resolve(i, i+K);
    }

    //for (int i=0; i<N; ++i) { cerr << B[i] << ' '; } cerr << endl;

    int empty = 0;
    int sum = 0;
    for (int i=0; i<K; ++i) {
        empty += (B[i] == -1);
        sum += (B[i] == 1);
    }

    int to_pick = A[0] - sum;
    cout << choose(empty, to_pick) << '\n';
}

