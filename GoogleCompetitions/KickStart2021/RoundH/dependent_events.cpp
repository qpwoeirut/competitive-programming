//dependent_events.cpp created at 11/13/21 21:09:29
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
const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 1001001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
ll P[MN];
ll par[MN];
//ll G[MN][MN];
set<ll> adj[MN];
string S, T;

int tin[MN], tout[MN];
int cur_time;
void dfs(const int u) {
    tin[u] = cur_time++;

    if (u != 0) P[u] = (P[par[u]] * A[u] + (1 - P[par[u]]) * B[u]) % MOD;
    if (P[u] < 0) P[u] += MOD;
    for (const int v: adj[u]) dfs(v);
    tout[u] = cur_time;
}

ll query(const int u, const int tar, const ll p) {
    if (u == tar) {
        return p;
    }

    for (const int v: adj[u]) {
        const ll pv = (p * A[v] + (1 - p) * B[v]) % MOD;
        const ll val = query(v, tar, pv < 0 ? pv + MOD : pv);
        if (val != -1) {
            return val;
        }
    }
    
    return -1;
}

bool is_anc(const int u, const int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

ll ans[MN];

void solve(int testcase) {
    const ll INV = binpow(1000000, MOD-2, MOD);
    assert(((INV * 1000000) % MOD) == 1);

    cur_time = 0;

    cin >> N >> Q;
    cin >> P[0];
    P[0] = (P[0] * INV) % MOD;
    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }

    for (int i=1; i<N; ++i) {
        cin >> par[i] >> A[i] >> B[i];
        --par[i];

        adj[par[i]].ins(i);

        A[i] = (A[i] * INV) % MOD;
        B[i] = (B[i] * INV) % MOD;
    }

    dfs(0);

    for (int i=0; i<Q; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        if (u > v) swap(u, v);

        debug(u, P[u]);
        debug(v, P[v]);
        debug(is_anc(u, v));
        if (is_anc(u, v)) {
            debug(u, v, query(u, v, 1));
            ans[i] = (P[u] * query(u, v, 1)) % MOD;
        } else {
            ans[i] = (P[u] * P[v]) % MOD;
        }
    }

    debug1(P, N);

    cout << "Case #" << testcase << ":";
    for (int i=0; i<Q; ++i) {
        cout << ' ' << ans[i];
    }
    cout << '\n';
}

int main() {
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
/*
2/10 32/100 296/1000 24/100 352/1000
*/

