//SLIPPERS.cpp created at 11/21/21 08:51:52
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

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

template <class T> using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <class T, class U> using ordered_map = tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

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

using _t=dbl;
using pt=complex<_t>;

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
const ll MOD = 998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 201001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll dp[MN];
ll BIT[MN];

void upd(int idx, ll val) {
    for (++idx; idx<MN; idx+=idx&-idx) BIT[idx] = (BIT[idx] + val) % MOD;
}

ll query(int idx) {
    ll ret = 0;
    for (++idx; idx>0; idx-=idx&-idx) ret += BIT[idx];
    return ret % MOD;
}

ll solve() {
    dp[0] = 1;
    upd(0, dp[0]);
    for (int i=0; i<N; ++i) {
        ll sum = query(A[i] - 1);
        ll old = dp[A[i]];
        dp[A[i]] += sum;
        dp[A[i]] %= MOD;
        
        upd(A[i], sum);
        //debug(i, A[i], old, sum);
        //debug(query(0), query(1), query(2), query(3), query(4), query(5));
        //debug1(dp, 8);
    }

    ll ans = 0;
    for (int x=0; x<MN; ++x) {
        ans += dp[x];
    }
    return ans % MOD;
}

const int BMX = 1001;
ll bdp[BMX][BMX];
ll brute() {
    for (int i=0; i<=N; ++i) {
        for (int x=0; x<BMX; ++x) {
            bdp[i][x] = 0;
        }
    }

    bdp[0][0] = 1;
    for (int i=1; i<=N; ++i) {
        for (int x=0; x<BMX; ++x) {
            // if x < A[i-1]: use A[i-1]
            // if x ≥ A[i-1]: don't use A[i-1]
            bdp[i][x] += bdp[i-1][x];
            if (bdp[i][x] >= MOD) bdp[i][x] -= MOD;
            if (x < A[i-1]) {  // if x = A[i-1] we cannot use A[i-1], covered above
                bdp[i][A[i-1]] += bdp[i-1][x];  // don't use A[i-1]
                if (bdp[i][A[i-1]] >= MOD) bdp[i][A[i-1]] -= MOD;
            }
        }
    }
    debug2(bdp, N+1, 8);

    ll ans = 0;
    for (int x=0; x<BMX; ++x) {
        ans += bdp[N][x];
        if (ans >= MOD) ans -= MOD;
    }
    return ans;
}

int main() {
    setIO();

    ll TEST_COUNT = 1;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        for (int i=0; i<N; ++i) cin >> A[i];
        cout << solve() << '\n';
        //brute();
    }

    return 0;
}
/*
dp[i][x] = subsets using first i items such that largest unused has val x
(i is 1-indexed)
if A[i] ≤ x:
    dp[i][x] = dp[i-1][x] + dp[i-1][x]
else:
    dp[i][x] = dp[i-1][x]
    dp[i][A[i]] += dp[i-1][x]

for all unused A[i]
    for all j | i < j and A[j] used
        A[i] < A[j]


dp[i] = subsets in A[0..i] where A[i] is rightmost largest unused
dp[j] = 1 + ∑(dp[i] * 2^k where k = # of values between A[i]..A[j])
ans = dp[N] (where A[N] = inf)

8
4 4 5 1 2 2 3 4

2
1 1
*/
