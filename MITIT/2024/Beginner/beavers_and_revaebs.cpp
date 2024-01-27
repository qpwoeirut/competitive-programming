#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 50;
const int MOD = 1e9 + 7;

ll binpow(ll x, ll p) {
    x %= MOD;
    ll ret = 1;
    for (; p > 0; p >>= 1) {
        if (p & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
    }
    return ret;
}

ll N;
int A[MN], B[MN];

int cur[MN];
int recurse(int idx) {
    if (idx == N) {
        int i = 0, j = N - 1;
        int s_i = 0, s_j = 0;
        while (i < N && j >= 0) {
            if (s_i <= s_j) {
                s_i += cur[i++];
            } else {
                s_j += cur[j--];
            }
            if (s_i == s_j) return 0;
        }
        return 1;
    }
    int ret = 0;
    for (int i=A[idx]; i<=B[idx]; ++i) {
        cur[idx] = i;
        ret += recurse(idx + 1);
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i] >> B[i];
    }
    if (N <= 8 && *max_element(B, B+N) <= 8) {
        int ans = recurse(0);
        cout << ans << '\n';
    } else {
        const ll k = B[0] - A[0] + 1;
        ll ans = (k * binpow(k - 1, N - 1)) % MOD;
        cout << ans << '\n';
    }

}

