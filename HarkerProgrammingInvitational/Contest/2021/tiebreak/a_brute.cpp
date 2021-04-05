#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;
typedef long long ll;

const int MN = 100005;
const ll MOD = 1e9 + 7;

int n;
int A[MN];

int pfac[MN];

map<int,int> fac[MN];

ll binpow(ll x, ll e) {
    ll ret = 1;
    for (; e>0; e>>=1) {
        if (e & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
    }
    return ret;
}

int brute() {
    assert(n <= 28);
    for (int i=0; i<n; ++i) {
        int tmp = A[i];
        while (tmp > 1) {
            int p = pfac[tmp];
            int ct = 0;
            while (tmp % p == 0) {
                tmp /= p;
                ++ct;
            }
            fac[i][p] = ct;
        }
    }

    ll ans = 1;
    for (int i=0; i<(1 << n); ++i) {
        map<int,int> ppows;
        for (int j=0; j<n; ++j) {
            if ((i >> j) & 1) {
                for (const pii& p: fac[j]) {
                    ppows[p.fi] = max(ppows[p.fi], p.se);
                }
            }
        }

        ll lcm = 1;
        for (const pii& p: ppows) lcm = (lcm * binpow(p.fi, p.se)) % MOD;

        ans = (ans * lcm) % MOD;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i=2; i<MN; ++i) {
        if (pfac[i] == 0) {
            for (int j=i; j<MN; j+=i) {
                pfac[j] = i;
            }
        }
    }

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> A[i];
    }

    cout << "brute: " << brute() << endl;
}
