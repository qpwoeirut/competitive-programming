#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;
using ll=long long;

#define fi first
#define se second

const int MN = 100005;
const ll MOD = 1e9 + 7;

int N;
int A[MN];

ll incr[MN], decr[MN];
ll incr_BIT[MN], decr_BIT[MN];
void upd(ll BIT[], int i, ll val) {
    for (; i<MN; i+=i&-i) BIT[i] = (BIT[i] + val) % MOD;
}
ll query(ll BIT[], int i) {
    ll ret = 0;
    for (; i>0; i-=i&-i) ret = (ret + BIT[i]) % MOD;
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=0; i<N; ++i) {
        incr[i] = query(incr_BIT, A[i] - 1) + 1;
        upd(incr_BIT, A[i], incr[i]);
    }
    for (int i=N-1; i>=0; --i) {
        decr[i] = query(decr_BIT, A[i] - 1) + 1;
        upd(decr_BIT, A[i], decr[i]);
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ans += (incr[i] * decr[i]) % MOD;
    }
    cout << ans % MOD << '\n';
}
