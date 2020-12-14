#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 10001;

ll N, MOD = 1e9 + 7;
ll dp[MN];

bool prime[MN];
bool ppow[MN];
int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);

    cin >> N >> MOD;
    prime[2] = true;
    for (int i=3; i<=N; i += 2) {
        prime[i] = true;
    }
    for (ll i=3; i<=N; i += 2) {
        if (!prime[i]) continue;
        for (ll j=i*i; j<=N; j += i) {
            prime[j] = false;
        }
    }
    for (ll i=2; i<=N; ++i) {
        if (!prime[i]) continue;
        for (ll j=i; j<=N; j*=i) {
            ppow[j] = true;
        }
    }
    //for (int i=1; i<=N; ++i) { cerr << prime[i] << ' '; } cerr << endl;

    for (ll i=1; i<=N; ++i) {
        if (!prime[i]) {
            continue;
        }
        for (ll j=N; j>=i; --j) {
            for (ll k=i; k<=j; k*=i) {
                dp[j] = (dp[j] + (dp[j-k] * k)) % MOD;
            }
        }
        for (ll k=i; k<=N; k*=i) {
            dp[k] = (dp[k] + k) % MOD;
        }

        //cerr << i << ": "; for (int j=1; j<=N; ++j) { cerr << dp[j] << ' '; } cerr << endl;
    }

    ll ans = 1;
    for (int i=1; i<=N; ++i) {
        ans = (ans + dp[i]) % MOD;
    }
    cout << ans << endl;
}

