//four_in_a_burrow.cpp created at 10/19/24 11:35:37
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

const int R = 6;
const int C = 7;
char G[R][C];

const int IN_PROGRESS = 0;
const int C_WINS = 1;
const int F_WINS = 2;
const int BOTH = 3;

char grid[R][C];
int check() {
    int result = 0;
    for (int r=0; r<R; ++r) {
        int ct_c = 0, ct_f = 0;
        for (int c=0; c<C; ++c) {
            if (grid[r][c] == 'C') ++ct_c;
            else ct_c = 0;
            if (grid[r][c] == 'F') ++ct_f;
            else ct_f = 0;

            if (ct_c >= 4) result |= C_WINS;
            if (ct_f >= 4) result |= F_WINS;
        }
    }

    for (int c=0; c<C; ++c) {
        int ct_c = 0, ct_f = 0;
        for (int r=0; r<R; ++r) {
            if (grid[r][c] == 'C') ++ct_c;
            else ct_c = 0;
            if (grid[r][c] == 'F') ++ct_f;
            else ct_f = 0;

            if (ct_c >= 4) result |= C_WINS;
            if (ct_f >= 4) result |= F_WINS;
        }
    }

    for (int s=0; s<R+C-1; ++s) {
        int ct_c = 0, ct_f = 0;
        for (int r=0; r<R; ++r) {
            int c = s - r;
            if (c < 0 || c >= C) continue;
            
            if (grid[r][c] == 'C') ++ct_c;
            else ct_c = 0;
            if (grid[r][c] == 'F') ++ct_f;
            else ct_f = 0;

            if (ct_c >= 4) result |= C_WINS;
            if (ct_f >= 4) result |= F_WINS;
        }
    }

    for (int s=-C; s<C; ++s) {
        int ct_c = 0, ct_f = 0;
        for (int r=0; r<R; ++r) {
            int c = s + r;
            if (c < 0 || c >= C) continue;
            
            if (grid[r][c] == 'C') ++ct_c;
            else ct_c = 0;
            if (grid[r][c] == 'F') ++ct_f;
            else ct_f = 0;

            if (ct_c >= 4) result |= C_WINS;
            if (ct_f >= 4) result |= F_WINS;
        }
    }

    return result;
}

int recurse(int col) {
    int ch = check();
    if (ch == BOTH) return 0;
    if (ch > 0 || col == C) return ch;

    int result = 0;
    for (int r=R; r>=0; --r) {
        for (int r0=0; r0<R; ++r0) {
            grid[r0][col] = r0 < r ? '.' : G[r0][col];
        }
        result |= recurse(col + 1);
        for (int r0=0; r0<R; ++r0) {
            grid[r0][col] = '.';
        }
    }
    return result;
}

void solve(int testcase) {
    for (int r=0; r<R; ++r) {
        for (int c=0; c<C; ++c) {
            cin >> G[r][c];
            grid[r][c] = '.';
        }
    }
    int result = recurse(0);
    char ans = "0CF?"[result];

    cout << "Case #" << testcase << ": " << ans << '\n';
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
3
FFCFFCF
FFCFFCF
FFCFFCF
CCFCCFC
CCFCCFC
CCFCCFC

CFFCFFF
FFCFFFF
FCFFFFF
CCCCCFC
CCCCCFC
CFCCCFC

CCCCCCC
CCCCCCC
CCFCFFC
FFFFFFC
FFFFFFC
FFFFFFC
*/
