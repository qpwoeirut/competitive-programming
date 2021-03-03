//lunch_concert.cpp created at 02/26/21 18:23:43

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<ll,ll> pll;

ll N;
map<ll,pll> A;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    ll cur = 0;
    ll L = 0, R = 0;
    for (int i=0; i<N; ++i) {
        ll p, w, d;
        cin >> p >> w >> d;
        A[p - d].fi += w;
        A[p + d].se += w;

        cur += abs<ll>(p - (d - 1e9)) * w;
        R += w;
    }

    ll ans = cur;
    ll prev = -1e9;
    for (const pair<ll,pll> &p: A) {
        //cerr << p.fi << ' ' << p.se.fi << ' ' << p.se.se << ' ' << cur << endl;
        cur += (L - R) * (p.fi - prev);
        L += p.se.se;
        R -= p.se.fi;

        ans = min(ans, cur);
        
        prev = p.fi;
    }

    cout << ans << endl;
}
