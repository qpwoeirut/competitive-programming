//1666c.cpp created at 04/15/22 16:02:39
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

using _t=ll;
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
pt A[3];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

void solve(int testcase) {
    cin >> A[0] >> A[1] >> A[2];
    sort(A, A+3);
    ll best = INF;
    vector<Line> ans;
    do {
        ll cur = 0;
        for (int i=0; i<2; ++i) cur += (ll)abs(A[i].x - A[i+1].x) + (ll)abs(A[i].y - A[i+1].y);
        if (best > cur) {
            best = cur;
            vector<pt> pts;
            for (int i=0; i<2; ++i) {
                pts.pb(A[i]);
                if (A[i].x != A[i+1].x && A[i].y != A[i+1].y) pts.eb(A[i].x, A[i+1].y);
            }
            pts.pb(A[2]);
            debug("a", cur);
            ans.clear();
            for (int i=0; i+1<pts.size(); ++i) {
                ans.eb(pts[i], pts[i+1]);
            }
        }
        const ll mnx = min(A[0].x, min(A[1].x, A[2].x));
        const ll mxx = max(A[0].x, max(A[1].x, A[2].x));
        const ll mny = min(A[0].y, min(A[1].y, A[2].y));
        const ll mxy = max(A[0].y, max(A[1].y, A[2].y));
        cur = mxx - mnx + abs(A[0].y - A[1].y) + abs(A[0].y - A[2].y);
        if (best > cur) {
            best = cur;
            debug("x", cur);
            ans.clear();
            const pt p1 = pt(mnx, A[0].y), p2 = pt(mxx, A[0].y);
            ans.eb(p1, p2);
            ans.eb(pt(A[1].x, A[0].y), A[1]);
            ans.eb(pt(A[2].x, A[0].y), A[2]);
        }
        cur = mxy - mny + abs(A[0].x - A[1].x) + abs(A[0].x - A[2].x);
        if (best > cur) {
            best = cur;
            debug("y", cur);
            ans.clear();
            const pt p1 = pt(A[0].x, mny), p2 = pt(A[0].x, mxy);
            ans.eb(p1, p2);
            ans.eb(pt(A[0].x, A[1].y), A[1]);
            ans.eb(pt(A[0].x, A[2].y), A[2]);
        }
    } while (next_permutation(A, A+3));

    assert(ans.size() > 0);
    cout << ans.size() << '\n';
    for (const Line& line: ans) {
        cout << line.p1.x << ' ' << line.p1.y << ' ' << line.p2.x << ' ' << line.p2.y << '\n';
    }
}

int main() {
    setIO();

    ll TEST_COUNT = 1;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
/*
0 0
10 3
11 -4
*/
