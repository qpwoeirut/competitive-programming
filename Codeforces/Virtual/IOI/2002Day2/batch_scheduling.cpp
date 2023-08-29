//batch_scheduling.cpp created at 08/28/23 15:18:28

#include <bits/stdc++.h>

using namespace std;
using ll=long long;

const int MN = 10000;
const ll INF = 1e18;

ll T[MN + 1];
ll F[MN + 1];

ll T_pref[MN + 1];
ll F_suff[MN + 1];
ll dp[MN + 1]; // [# of jobs] = waste
ll min_dp[MN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll N;
    ll S;
    cin >> N;
    cin >> S;

    for (int i=1; i<=N; ++i) {
        cin >> T[i] >> F[i];
    }
    
    T_pref[0] = 0;
    for (int i=1; i<=N; ++i) {
        T_pref[i] = T_pref[i-1] + T[i];
    }
    F_suff[N] = 0;
    for (int i=N-1; i>=0; --i) {
        F_suff[i] = F_suff[i+1] + F[i+1];
    }

    fill(dp, dp+N+1, INF);
    dp[0] = 0;
    for (int job=1; job<=N; ++job) {
        ll job_waste = 0;
        for (int i=job - 1; i>=0; --i) {
            job_waste += F[i + 1] * (T_pref[job] - T_pref[i + 1]);
            const ll batch_waste = S * F_suff[i];
            dp[job] = min(dp[job], dp[i] + job_waste + batch_waste);
        }
        cerr << job << ' ' << dp[job] << endl;
    }

    ll ans = dp[N];
    for (int i=1; i<=N; ++i) {
        ans += F[i] * T_pref[i];
    }

    cout << ans << '\n';
}

