//robreplace.cpp created at 02/07/21 11:28:49
// AC with 3:20:58 remaining
// 11:42am

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 2000006;

ll N, X, K;
ll A[MN];
ll psum[MN];
ll raft[MN];

int main() {
    freopen("robreplace.in", "r", stdin);
    freopen("robreplace.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> X >> K;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
    }
    psum[0] = 0;
    for (int i=1; i<=N; ++i) {
        psum[i] = psum[i-1] + A[i];
    }
    for (int i=N+1; i<=N+K; ++i) {
        psum[i] = psum[i-1];
    }

    ll ans = 0;
    int fast = -1;
    multiset<ll> raft;
    for (int i=1; i<=N; ++i) {
        while (fast < N && psum[fast + 1] - psum[i-1] <= X) {
            ++fast;
            raft.insert(psum[fast + K] - psum[fast]);
        }
        const ll cover = *raft.rbegin() + X;
        const ll hi = upper_bound(psum, psum + N + 1, psum[i-1] + cover) - psum;
        ans = max(ans, hi - i);

        raft.erase(raft.find(psum[i + K - 1] - psum[i - 1]));
    }

    cout << ans << endl;
}
