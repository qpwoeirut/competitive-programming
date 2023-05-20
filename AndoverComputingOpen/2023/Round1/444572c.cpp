//444572c.cpp created at 05/20/23 11:27:22
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

int egcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = egcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

bool solve(ll p, ll q, ll x, ll y) {
    if (x == 0 && y == 0) {
        return true;
    }

    int ax = 0, bx = 0, gx = 0;
    if (!find_any_solution(p, q, x, ax, bx, gx)) {
        return false;
    }
    int ay = 0, by = 0, gy = 0;
    if (!find_any_solution(p, q, y, ay, by, gy)) {
        return false;
    }
    debug(ax, bx, gx, ay, by, gy);

    if ((ax + bx)  == (ay + by) ) {
        return true;
    } else {
        return false;
    }
}

bool brute(ll p, ll q, ll x, ll y) {
    set<pii> vis;
    queue<pii> qu;
    qu.emplace(0, 0);
    vis.emplace(0, 0);

    array<ll, 8> chx = {p, p, -p, -p, q, q, -q, -q};
    array<ll, 8> chy = {q, -q, q, -q, p, -p, p, -p};

    int ct = 1000000;
    while (qu.size() > 0 && --ct >= 0) {
        pii cur = qu.front(); qu.pop();
        if (cur.fi == x && cur.se == y) return true;

        for (int i=0; i<8; ++i) {
            pii nxt(cur.fi + chx[i], cur.se + chy[i]);
            if (vis.insert(nxt).se == true) continue;
            qu.push(nxt);
        }
    }
    return false;
}

void test() {
    mt19937 rng(8);
    const ll MX = 50;
    for (int t=0; t<100000; ++t) {
        ll p = rng() % MX;
        ll q = rng() % MX;
        ll x = rng() % MX;
        ll y = rng() % MX;
        bool sans = solve(p, q, x, y);
        bool bans = brute(p, q, x, y);
        if (sans != bans) {
            cout << p << ' ' << q << ' ' << x << ' ' << y << endl;
            cout << sans << ' ' << bans << endl;
        }
        assert(sans == bans);
    }
}

int main() {
    setIO();

    //test(); return 0;

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        ll p, q, x, y;
        cin >> p >> q >> x >> y;
        p = abs(p);
        q = abs(q);
        x = abs(x);
        y = abs(y);
        cout << (solve(p, q, x, y) ? "YES" : "NO") << '\n';
    }

    return 0;
}
/*
23 48 31 29
23 48 81 29
*/
