#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

typedef pair<int,int> pii;
typedef long long ll;
const int MN = 100005;
const ll MOD = 1e9 + 7;
#define MAXV 100100

int n;
int A[MN];
namespace solution {
    int cnt[MAXV];
    vector<int> factors[MAXV];
    bool prime[MAXV];
    map<int, map<int,int> > ppows;

    ll binexp(ll v, ll p, ll m) {
        if (p == 0) return 1ll;
        if (p == 1) return v % m;
        if (p % 2) return (v * binexp(v, p-1, m) + m) % m;
        return binexp((v*v+m)%m, p/2, m);
    }

    int solve() {
        memset(cnt, 0, sizeof(cnt));
        ppows.clear();
        fill(factors, factors+MAXV, vector<int>());

        for (int i = 0; i < n; i++) {
            cnt[A[i]]++;
        }

        memset(prime, true, sizeof(prime));

        for (ll i = 2; i < MAXV; i++) {
            if (!prime[i]) continue;

            factors[i].push_back(i);

            for (ll j = i * 2; j < MAXV; j += i) {
                prime[j] = false;
                factors[j].push_back(i);
            }
        }

        for (ll i = 2; i < MAXV; i++) {
            if (cnt[i] == 0) continue;
            for (ll j : factors[i]) {
                ll v = i, np = 0;
                while (v % j == 0)
                    v /= j, np++;
                ppows[j][np] += cnt[i];
            }
        }

        ll ans = 1;
        for (auto j : ppows) {

            ll tot = 0;

            for (auto i : j.second)
                tot += i.second;

            for (int i = 1; i <= j.second.rbegin()->first; i++) {

                ll nsubsets = binexp(2, tot, MOD - 1) - 1ll;
                ll nother = binexp(2, n - tot, MOD - 1);
                ll res = nsubsets * nother;


                res = binexp(j.first, res, MOD);
                ans = (ans * res + MOD) % MOD;

                tot -= j.second[i];
            }

        }

        return ans;
    }
}


namespace brute {
    typedef pair<int,int> pii;
    typedef long long ll;

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

        fill(pfac, pfac+MN, 0);
        fill(fac, fac+MN, map<int,int>());
        for (int i=2; i<MN; ++i) {
            if (pfac[i] == 0) {
                for (int j=i; j<MN; j+=i) {
                    pfac[j] = i;
                }
            }
        }

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
}

void test() {
    for (n=1; n<=20; ++n) {
        cerr << n << endl;
        for (int t=0; t<100; ++t) {
            for (int i=0; i<n; ++i) {
                A[i] = (rand() % 100000) + 1;
            }

            int bans = brute::brute();
            int ans = solution::solve();

            if (ans != bans) {
                cout << n << '\n';
                for (int i=0; i<n; ++i) {
                    cout << A[i] << ' ';
                } cout << endl;

                cout << ans << ' ' << bans << endl;
            }
            assert(ans == bans);
        }
    }
}

int main() {
    test(); return 0;
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i=0; i<n; ++i) {
        cin >> A[i];
    }

    cout << brute::brute() << '\n';
    cout << solution::solve() << '\n';
}
/*
1
16808
*/
