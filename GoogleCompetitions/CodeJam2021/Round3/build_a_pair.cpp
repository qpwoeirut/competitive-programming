//build_a_pair.cpp created at 06/05/21 07:02:47

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL
#include "qpwoeirut/debug.h"
#else
#define debug
#define debug1
#define debug2
#define debug3
#endif

#define pb push_back
#define ins insert

#define fi first
#define se second
#define sz(obj) ((int)(obj.size()))
#define all(obj) begin(obj), end(obj)

#define LB lower_bound
#define UB upper_bound

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

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

ll gcd(ll a, ll b) {return b ? gcd(b, a%b) : a;}

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
const dbl EPS = 1e-16;

#define x real()
#define y imag()

typedef PUT_SMTH_HERE _t; 
typedef complex<_t> pt;

template <class T> string to_string(const complex<T>& p) {
    return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

namespace std {
    inline bool operator<(const pt& a, const pt& b) {
        if (abs(a.x - b.x) > EPS) return a.x < b.x;
        if (abs(a.y - b.y) > EPS) return a.y < b.y;
        return false;
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
};

// (hopefully) returns +1 for counterclockwise turn, -1 for clockwise turn, 0 for collinear
int ccw(const pt& a, const pt& b, const pt& c) {
    const _t dx1 = b.x - a.x, dy1 = b.y - a.y;
    const _t dx2 = c.x - a.x, dy2 = c.y - a.y;
    if (dx1 * dy2 < dx2 * dy1) return +1;
    if (dx1 * dy2 > dx2 * dy1) return -1;
    return 0;
}
#endif

void setIO(const string& filename = "") {
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
	cin.tie(0)->sync_with_stdio(0);
}

int chr[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
int chc[8] = {0, 1, 0, -1, -1, 1, -1, 1};

const ll MOD = 1e9+7; //998244353; //1e9+9; //1e9+21; //1e9+33;
const int INIT = 1001001001;
const int MN = 1001001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN], B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll brute() {
    T = S;
    ll best = INF;
    sort(all(T));
    N = sz(T);
    do {
        if (T[0] == '0' || T[(N+1)/2] == '0') continue;
        ll x = 0, y = 0;
        for (int i=0; i<(N+1)/2; ++i) {
            x *= 10; x += T[i] - '0';
            if (i + (N+1)/2 < N) {
                y *= 10; y += T[i + (N+1)/2] - '0';
            }
        }
        if (chmn(best, abs(x - y))) {
            debug(x, y);
        }
    } while (next_permutation(all(T)));

    return best;
}

ll ct[10];
ll pw[19];

ll calc(int dup) {
    //debug(dup);
    bool pairs = false;
    N = 0;
    int zct = 0;
    for (int i=0; i<10; ++i) {
        int n = ct[i];
        while (n > 3) n -= 2;
        if (i != dup && n >= 2) n -= 2;
        for (int j=0; j<n; ++j) A[N++] = i;
        if (i == 0) zct = (ct[i] - n) / 2;
        if (i > 0 && ct[i] != n) pairs = true;
    }

    if (N == 0) return 0;

    assert(N % 2 == 0);
    //debug1(A, N);
    //debug(zct);

    ll best = INF;
    do {
        bool p10 = false;
        if (!pairs && (A[0] == 0 || A[N/2] == 0)) continue;
        ll x = 0, y = 0;
        for (int i=0; i<N/2; ++i) {
            if (!pairs && i > 0 && !p10 && x == y) {
                x *= pw[zct];
                y *= pw[zct];
                p10 = true;
            }
            x *= 10; x += A[i];
            y *= 10; y += A[i + N/2];
        }
        if (!pairs && !p10) {
            x *= pw[zct];
            y *= pw[zct];
        }
        if (chmn(best, abs(x - y))) {
            //debug(x, y); debug1(A, N);
        }
    } while (next_permutation(A, A+N));

    return best;
}

int ct2[10];
ll greedy() {
    deque<int> digits;
    for (int i=0; i<10; ++i) {
        ct2[i] = ct[i] & 1;
        if (i == 0) ct2[i] = ct[i];
    }

    ll best = INF;
    for (int i=1; i<10; ++i) {
        for (int j=i+1; j<10; ++j) {
            if (ct2[i] == 0 || ct2[j] == 0) continue;
            digits.clear();
            for (int d=0; d<10; ++d) {
                if (d != i && d != j) {
                    for (int k=0; k<ct2[d]; ++k) digits.pb(d);
                }
            }
            ll x = j, y = i;
            while (digits.size() > 0) {
                x *= 10; x += digits.front(); digits.pop_front();
                assert(digits.size() > 0);
                y *= 10; y += digits.back(); digits.pop_back();
            }

            chmn(best, abs(x - y));
        }
    }

    return best;
}

ll solve() {
    sort(all(S));
    fill(ct, ct+10, 0);
    for (const char c: S) ++ct[c - '0'];
    ll best = INF;
    if (sz(S) & 1) {
        ll x = 0, y = 0;
        int i=0, j=9;
        for (int d=1; d<10; ++d) {
            if (ct[d]) {
                x += d;
                --ct[d];
                break;
            }
        }
        while (i <= j) {
            while (i<10 && ct[i] == 0) ++i;
            if (i < 10) {
                x *= 10; x += i;
                --ct[i];
            }

            while (j>=0 && ct[j] == 0) --j;
            if (j >= 0) {
                y *= 10; y += j;
                --ct[j];
            }
        }
        best = abs(x - y);
        //debug(x, y);
    } else {
        vector<int> same;
        for (int i=0; i<10; ++i) {
            if (ct[i] >= 2) same.pb(i);
        }
        if (same.empty()) {
            same.pb(-1);
        }
        for (const int s: same) {
            chmn(best, calc(s));
        }
        chmn(best, greedy());
    }

    return best;
}

void test() {
    for (int t=0; t<100000; ++t) {
        ll x = rand();
        debug(x);
        S = to_string(x);
        int zct = count(all(S), '0');
        if (zct + 2 > sz(S)) continue;
        ll ans = solve();
        ll bans = brute();
        if (ans != bans) {
            debug(S, ans, bans);
        }
        assert(ans == bans);
    }
}

int main() {
    setIO();

    pw[0] = 1;
    for (int i=1; i<=18; ++i) pw[i] = pw[i-1] * 10;

    //test(); return 0;
    
    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> S;
        ll ans = solve();
        cout << "Case #" << test_case << ": " << ans << '\n';
    }
    
    return 0;
}
/*
1000450009
0116
000116
001111
000556
0000234589
*/
