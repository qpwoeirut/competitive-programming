#include <bits/stdc++.h>

using namespace std;

using ll=long long;

const int MN = 100005;

int N, Q;
ll A[MN], query[MN];
ll sum;

ll solve(const ll q) {
    if (sum % q) return -1;

    ll ans = 0;
    ll cur = 0;
    for (int i=0; i<N; ++i) {
        cur += A[i];
        //cerr << q << ' ' << i << ' ' << cur << ' ' << ans << endl;
        if (cur >= q) {
            ans += (cur - 1) / q;
            cur %= q;
        }
        if (cur > 0) {
            ++ans;
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        for (int i=0; i<N; ++i) sum += A[i];
    }
    cin >> Q;
    int q;
    for (int i=0; i<Q; ++i) {
        cin >> q;
        cout << solve(q) << '\n';
    }
}

/*
1
1000000000000
1
1
*/
