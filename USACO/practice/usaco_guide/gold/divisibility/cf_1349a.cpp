//cf_1349a.cpp created at 12/19/20 13:26:16

#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef long long ll;

const int MN = 100005;
const int MX = 200005;

int N;
int A[MN];
int pf[MX];

ll binpow(ll x, ll p) {
    ll ret = 1;
    while (p > 0) {
        if (p & 1) ret *= x;
        x *= x;
        p >>= 1;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }

    for (int i=2; i<MX; ++i) {
        if (pf[i] == 0) {
            for (int j=i; j<MX; j+=i) {
                pf[j] = i;
            }
        }
    }

    map<ll,vector<int>> pfac;
    for (int i=0; i<N; ++i) {
        int x = A[i];

        while (x > 1) {
            const int p = pf[x];
            int ct = 0;
            while (x % p == 0) {
                x /= p;
                ++ct;
            }

            pfac[p].push_back(ct);
        }
    }

    ll ans = 1;
    for (auto p: pfac) {
        if (p.se.size() == N-1) p.se.push_back(0);
        if (p.se.size() < N) continue;
        //cerr << p.fi << ' '; for (auto x: p.se) cerr << x << ' '; cerr << endl;
        nth_element(p.se.begin(), p.se.begin() + 1, p.se.end());
        ans *= binpow(p.fi, p.se[1]);
    }

    cout << ans << endl;
}
