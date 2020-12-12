#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pll;

const int MN = 100005;
const ll MOD = 1e9 + 7;

ll N;
pll A[MN];
ll p2[MN];
int pct[MN << 1], sct[MN << 1];

int main() {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i].fi >> A[i].se;
        ++sct[A[i].fi];
        ++pct[A[i].se];
    }
    pct[0] = 0;
    for (int i=1; i<=2*N; ++i) {
        pct[i] += pct[i-1];
    }
    sct[2*N + 1] = 0;
    for (int i=2*N; i>=0; --i) {
        sct[i] += sct[i+1];
    }

    p2[0] = 1;
    for (int i=1; i<=N; ++i) {
        p2[i] = p2[i-1] << 1;
        if (p2[i] >= MOD) p2[i] -= MOD;
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        ll ct = pct[A[i].fi - 1] + sct[A[i].fi + 1];
        //cerr << i << ' ' << A[i].fi << ' ' << A[i].se << ' ' << ct << ' ' << p2[ct] << endl;
        ans = (ans + p2[ct]) % MOD;
    }

    cout << ans << endl;
}
