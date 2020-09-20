//cyclic_array.cpp created at 09/17/20 11:23:58

#include <bits/stdc++.h>

using namespace std;

#define FI first
#define SE second

typedef long long ll;
typedef pair<ll,ll> pll;

const ll MN = 200001;

ll N, K;
ll A[MN];
pll dp[MN];

int main() {
    cin >> N >> K;

    ll sum = 0;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        sum += A[i];
    }

    if (N == 1) {
        cout << 1 << endl;
        return 0;
    }

    int L = 1;
    ll cur = sum - A[0];
    for (int R=0; R<N; ++R) {
        cur += A[R];
        while (cur > K) {
            cur -= A[L];
            L = (L + 1) % N;
        }
        if (L > R) {
            dp[R] = pll(1, L);
        } else if (L == 0) {
            dp[R] = pll(1, N);
        } else {
            dp[R] = pll(dp[L - 1].FI + 1, dp[L - 1].SE);
        }
    }

    ll ans = N;
    for (int i=0; i<N; ++i) {
        if (dp[i].FI != 1) break;
        ans = min(ans, dp[dp[i].SE - 1].FI + (dp[dp[i].SE - 1].SE > dp[i].SE ? 1 : 0));
    }
    cout << ans << endl;
}
