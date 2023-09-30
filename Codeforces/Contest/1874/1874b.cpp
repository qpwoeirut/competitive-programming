//1874b.cpp created at 09/30/23 08:07:56
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

ll solve(ll a, ll b, ll c, ll d, ll m) {
    bool bad = false;
    for (int sh = 0; sh < 30; ++sh) {
        int aa = (a >> sh) & 1;
        int bb = (b >> sh) & 1;
        int cc = (c >> sh) & 1;
        int dd = (d >> sh) & 1;
        int mm = (m >> sh) & 1;
        if (mm == 0 && (aa != cc || bb != dd)) {
            if (cc == 0 && dd == 1) bad = true;
            if (aa == 0 && bb == 0) bad = true;
        }
        for (int sh2 = 0; sh2 < 30; ++sh2) {
            int aaa = (a >> sh2) & 1;
            int bbb = (b >> sh2) & 1;
            int ccc = (c >> sh2) & 1;
            int ddd = (d >> sh2) & 1;
            int mmm = (m >> sh2) & 1;
            if (aa == aaa && bb == bbb && mm == mmm && (cc != ccc || dd != ddd)) bad = true;
            if (aa == cc && aa == 0 && bb == dd && bb == 1 && mm == 0 && aaa == 0 && bbb == 0 && ccc == 1 && mmm == 1) bad = true;
        }
    }
    map<pll, ll> cost;
    queue<pll> q;
    q.emplace(a, b);
    while (q.size() > 0) {
        ll cur_cost = cost[q.front()];  // default 0
        ll x = q.front().fi, y = q.front().se; q.pop();
        //debug(x, y, cur_cost);
        if (x == c && y == d) {
            //debug(a, b, c, d, m, cur_cost);
            assert(!bad);
            return cur_cost;
        }

        pll op1(x & y, y), op2(x | y, y), op3(x, x ^ y), op4(x, y^m);
        if (cost.count(op1) == 0) cost[op1] = cur_cost + 1, q.push(op1);
        if (cost.count(op2) == 0) cost[op2] = cur_cost + 1, q.push(op2);
        if (cost.count(op3) == 0) cost[op3] = cur_cost + 1, q.push(op3);
        if (cost.count(op4) == 0) cost[op4] = cur_cost + 1, q.push(op4);
    }
    if (!bad) debug(a, b, c, d, m);
    return -1;
}

void test() {
    for (int sh = 0; sh <= 2; ++sh) {
        const ll MAX_VAL = 1 << sh;
        debug(sh, MAX_VAL);

        ll mx = 0;
        for (ll a=0; a<MAX_VAL; ++a) {
            for (ll b=0; b<MAX_VAL; ++b) {
                for (ll c=0; c<MAX_VAL; ++c) {
                    for (ll d=0; d<MAX_VAL; ++d) {
                        for (ll m=0; m<MAX_VAL; ++m) {
                            chmx(mx, solve(a, b, c, d, m));
                        }
                    }
                }
            }
        }
        debug(mx);
    }
}

int main() {
    setIO();

    test(); return 0;

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        ll a, b, c, d, m;
        cin >> a >> b >> c >> d >> m;
        ll ans = solve(a, b, c, d, m);
        cout << ans << '\n';
    }

    return 0;
}
