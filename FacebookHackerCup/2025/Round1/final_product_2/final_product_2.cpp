//final_product_2.cpp created at 10/18/25 10:24:42
#include <bits/stdc++.h>

using namespace std;

#ifdef DELETE_FOR_PBDS
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
#endif

#define pb push_back
#define eb emplace_back
#define ins insert
#define emp emplace

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pcll = pair<const ll,ll>;

using ull = unsigned long long;
using dbl = long double;
using pib = pair<int,bool>;
using plb = pair<ll,bool>;
using pdd = pair<dbl,dbl>;
using mii = map<int,int>;
using mll = map<ll,ll>;
using mci = map<char,int>;
using msi = map<string,int>;
using mss = map<string,string>;

ll binpow(ll x, ll p, const ll& mod) {assert(mod>0);
    ll ret = 1;
    for(; p>0; p>>=1, x = x*x % mod) if(p & 1) ret = ret*x % mod;
    return ret;
}

template <class T> bool chmn(T& a, const T& b) {return (greater<T>()(a, b) ? (a=b, true) : false);}
template <class T> bool chmx(T& a, const T& b) {return (less<T>()(a, b) ? (a=b, true) : false);}

template <class T> T square(const T& a) {return a*a;}
template <class T> T cube(const T& a) {return a*a*a;}

#ifdef DELETE_THIS_IN_CASE_OF_GEO
using _t=PUT_SMTH_HERE;
using pt=complex<_t>;

const dbl EPS = 1e-16;

#define x real()
#define y imag()

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        if (abs(a.x - b.x) > EPS) return a.x < b.x;
        if (abs(a.y - b.y) > EPS) return a.y < b.y;
        return false;
    }
    inline bool operator>(const pt& a, const pt& b) {
        return b < a;
    }
}

struct Line {
    pt p1, p2;
    Line() {
        p1 = p2 = pt(0, 0);
    }
    Line(const pt& _p1, const pt& _p2) {
        p1 = min(_p1, _p2);
        p2 = max(_p1, _p2);
    }
    Line(const _t a, const _t b, const _t c, const _t d) {
        p1 = pt(a, b);
        p2 = pt(c, d);
        if (p1 > p2) swap(p1, p2);
    }
    inline bool operator<(const Line& o) const {
        return p1 < o.p1 || (p1 == o.p1 && p2 < o.p2);
    }
};

namespace std {
    inline bool operator<(const Line& a, const Line& b) {
        return a.p1 < b.p1 || (a.p1 == b.p1 && a.p2 < b.p2);
    }
}

istream& operator>>(istream& is, pt& p) {
    _t a, b;
    is >> a >> b;
    p = pt(a, b);
    return is;
}
istream& operator>>(istream& is, Line& p) {
    _t a, b, c, d;
    is >> a >> b >> c >> d;
    p = Line(a, b, c, d);
    return is;
}

string to_string(const complex<_t>& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}
string to_string(const Line& a) {
    return "(" + to_string(a.p1) + "--" + to_string(a.p2) + ")";
}
#endif

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll INF = 2e18 + 1;
const int INIT = 1001001001;
const int LG = 24;
const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 1001001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll* fact;
ll choose(ll n, ll k) {
    assert(n >= k);
    ll invfk = binpow(fact[k % MOD], MOD - 2, MOD);
    ll invfnk = binpow(fact[(n - k + MOD) % MOD], MOD - 2, MOD);
    return (((fact[n % MOD] * invfk) % MOD) * invfnk) % MOD;
}

unordered_map<ll, ll> dp[71];

void solve(int testcase) {
    ll a, b;
    cin >> N >> a >> b;

    for (int i=0; i<71; ++i) dp[i].clear();

    const ll X = min(N, 70LL);

    set<ll> factor;
    for (ll i=1; i*i<=b; ++i) {
        if (b%i == 0) {
            factor.insert(i);
            factor.insert(b / i);
        }
    }
    debug(b, factor.size());//, factor);

    dp[0][1] = 1;
    for (int i=0; i+1<=X; ++i) {
        //debug(i, dp[i].size());
        for (const auto [cur, ct]: dp[i]) {
            for (const ll f: factor) {
                if (f == 1 || cur > b/f || factor.count(cur * f) == 0) continue;
                dp[i+1][cur * f] += ct;
                dp[i+1][cur * f] %= MOD;
            }
        }
    }
    assert(dp[70].empty());

    ll ans = 0;
    for (const ll f: factor) {
        if (f > a) continue;

        for (int k1=0; k1<=X; ++k1) {
            const auto it1 = dp[k1].find(f);
            if (it1 == dp[k1].end()) continue;
            const ll ways1 = (choose(N, k1) * it1->se) % MOD;
            for (int k2=0; k2<=X; ++k2) {
                const auto it2 = dp[k2].find(b / f);
                if (it2 == dp[k2].end()) continue;
                const ll ways2 = (choose(N, k2) * it2->se) % MOD;
                //debug(f, k1, it1->se, ways1, k2, it2->se, ways2);

                ans += (ways1 * ways2) % MOD;
            }
        }
    }
    ans %= MOD;

    cout << "Case #" << testcase << ": " << ans << '\n';
}

int main() {
    setIO();

    fact = new ll[MOD];
    fact[0] = 1;
    for (ll i=1; i<MOD; ++i) {
        fact[i] = (fact[i-1] * i) % MOD;
        if ((i & 67108863) == 0) debug(i);
    }

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
/*
2
10000000000000000 60850052705442 60850052705442
10000000000000000 70368744177664 70368744177664
*/
