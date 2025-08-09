//2128e.cpp created at 07/27/25 08:07:40
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

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
            for (int j=0; j<sz(jmp[k]); ++j) {
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

pll check(ll x, bool qmin = false) {
    vector<pll> sum(N+1);
    for (int i=1; i<=N; ++i) {
        if (qmin) {
            sum[i].fi = sum[i - 1].fi + (x >= A[i - 1] ? -1 : +1);
        } else {
            sum[i].fi = sum[i - 1].fi + (x <= A[i - 1] ? -1 : +1);
        }
        sum[i].se = i - 1;
    }
    RMQ rmq(sum);
    
    for (int i=0; i+K<=N; ++i) {
        pll res = rmq.query(i+K, N+1);
        if (sum[i].fi >= res.fi) return pll(i, res.se);
    }
    return pll(-1, -1);
}

void solve(int testcase) {
    cin >> N >> K;
    for (int i=0; i<N; ++i) cin >> A[i];


    ll lo = 0, hi = N + 1;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (check(mid).fi != -1) lo = mid;
        else hi = mid - 1;
    }
    ll mx = lo;
    pll int_mx = check(mx);

    lo = 0, hi = N + 1;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (check(mid, true).fi == -1) lo = mid;
        else hi = mid - 1;
        debug(lo, hi);
    }

    ll mn = lo + 1;
    pll int_mn = check(mn, true);

    cout << mx - mn + 1 << '\n';
    cout << mn << ' ' << int_mn.fi+1 << ' ' << int_mn.se+1 << '\n';
    ++mn;

    lo = int_mn.fi, hi = int_mn.se;
    multiset<ll> big, small;
    for (int i=lo; i<=hi; ++i) big.ins(A[i]);
    while (big.size() > small.size() + 1) {
        small.ins(*big.begin());
        big.erase(big.begin());
    }
    while (mn <= mx) {
        if (int_mx.fi < lo) {
            big.ins(A[--lo]);
        } else if (hi < int_mx.se) {
            big.ins(A[++hi]);
        } else if (lo < int_mx.fi) {
            if (big.find(A[lo]) != big.end()) big.erase(big.find(A[lo]));
            else small.erase(small.find(A[lo]));
            ++lo;
        } else if (int_mx.se < hi) {
            if (big.find(A[hi]) != big.end()) big.erase(big.find(A[hi]));
            else small.erase(small.find(A[hi]));
        }
        if (big.size() > small.size() + 1) {
            small.ins(*big.begin());
            big.erase(big.begin());
        }

        ll mhi = *big.begin();
        for (; mn <= mx && mn <= mhi; ++mn) {
            cout << mn << ' ' << lo+1 << ' ' << hi+1 << '\n';
        }
    }

    debug(mn, int_mn, mx, int_mx);
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
