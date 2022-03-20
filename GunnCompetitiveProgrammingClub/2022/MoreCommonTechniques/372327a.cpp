#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const ll MOD = 998244353;

int N, M;

int A[8];
ll pows[105];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        A[i] = i+1;
    }

    pows[0] = 2022;
    for (int i=1; i<N; ++i) {
        pows[i] = (pows[i-1] * 2022) % MOD;
    }

    ll best = 1e18;
    do {
        ll cost = 0;
        for (int i=0; i<N; ++i) {
            cost += pows[i] * A[i % M];
        }
        best = min(best, cost);
    } while (next_permutation(A, A+M));

    cout << best << '\n';
}
