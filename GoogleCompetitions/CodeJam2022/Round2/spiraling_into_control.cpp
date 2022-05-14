//spiraling_into_control.cpp created at 05/14/22 07:36:23
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

ll spiral(int r, int c) {
    const ll center = N / 2;
    const ll r_off = r - center;
    const ll c_off = c - center;
    const ll section = max(abs(r_off), abs(c_off));
    const ll start = N * N - square(2 * section + 1) + 1;

    if (r + section == center) return start + c_off + section * 1;
    if (center + section == c) return start + r_off + section * 3;
    if (center + section == r) return start - c_off + section * 5;
    if (c + section == center) return start - r_off + section * 7;
    assert(0);
}

vector<pll> solve() {
    vector<pll> ans;
    if (K % 2 == 1 || K < N-1) {
        return ans;
    }

    ll rem = N * N - 1 - K;
    ll r = 0, c = 0;
    while (r != N / 2 || c != N / 2) {
        int dir = -1;
        ll jump = 0;
        const ll cur_val = spiral(r, c);
        for (int i=0; i<4; ++i) {
            const int nr = r + chr[i], nc = c + chc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            const ll diff = spiral(nr, nc) - cur_val;
            if (rem >= diff-1 && chmx(jump, diff)) dir = i;
        }

        if (jump <= 0) {
            return vector<pll>();
        }

        if (jump > 1) {
            ans.eb(cur_val, spiral(r + chr[dir], c + chc[dir]));
        }

        rem -= jump - 1;
        r += chr[dir];
        c += chc[dir];
    }
    if (rem > 0) return vector<pll>();

    return ans;
}

void test() {
    for (N=9991; N<=9999; N+=2) {
        debug(N);
        for (K=1; K<N*N-1; ++K) {
            const vector<pll> ans = solve();
            if (ans.empty()) {
                assert(K % 2 == 1 || K < N);
            } else {
                ll k = K;
                int cur = 1;
                for (const pll& p: ans) {
                    k -= p.fi - cur;
                    cur = p.se;
                    --k;
                }
                k -= N*N - cur;
                assert(k == 0);
            }
        }
    }
}

int main() {
    test(); return 0;
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N >> K;

        const vector<pll> ans = solve();
        if (ans.empty()) {
            cout << "Case #" << test_case << ": IMPOSSIBLE" << '\n';
        } else {
            cout << "Case #" << test_case << ": " << ans.size() << '\n';
            for (const pll& p: ans) {
                cout << p.fi << ' ' << p.se << '\n';
            }
        }
    }

    return 0;
}
