#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 5001;
const int MOD = 1e9 + 7;

ll N, M, K;
ll A[MN], B[MN];

ll kn[MN];
ll ct[26], ways[MN];

ll binpow(ll x, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) {
            ret = (ret * x) % MOD;
        }
        p >>= 1;
        x = (x * x) % MOD;
    }
    return ret;
}

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
        --B[i];
    }

    for (int i=0; i<M; ++i) {
        char e;
        cin >> e;
        ++ct[e - 'A'];
    }

    kn[0] = 1;
    for (int i=1; i<K; ++i) {
        for (int j=0; j<N; ++j) {
            if (i >= A[j]) {
                kn[i] += kn[i - A[j]];
                if (kn[i] >= MOD) kn[i] -= MOD;
            }
        }
    }
    for (int i=0; i<N; ++i) {
        ways[B[i]] += kn[K - A[i]];
        if (ways[B[i]] >= MOD) ways[B[i]] -= MOD;
    }

    ll ans = 1;
    for (int i=0; i<26; ++i) {
        if (ct[i] == 0) continue;
        ll cur = 0;
        for (int j=0; j<N; ++j) {
            if (ways[j] == 0) continue;
            cur = (cur + binpow(ways[j], ct[i])) % MOD;
        }
        ans = (ans * cur) % MOD;
    }

    cout << ans << endl;
}
    
