//1662i.cpp created at 05/06/22 16:50:24
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

ll d[MN];
bool check(const ll a, const ll b) {
    if (d[a] == 0 || d[b] == 0) return false;
    const ll pa = a * 100;
    const ll pb = b * 100;
    const dbl pos = pa + d[a] - 0.1;
    return pb < pos || pb - d[b] <= pos;
}

ll sum[MN];

ll solve() {
    sort(B, B+M);
    for (int i=0; i<N; ++i) {
        sum[i+1] = sum[i] + A[i];
    }
    int cur = 0;
    for (int i=0; i<N; ++i) {
        const ll pos = i * 100;
        d[i] = abs(pos - B[cur]);
        while (cur + 1 < M && abs(pos - B[cur + 1]) <= d[i]) {
            cur++;
            d[i] = abs(pos - B[cur]);
        }
    }

    int slow = 0;
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        while (slow <= i && !check(slow, i)) ++slow;
        chmx(ans, sum[i+1] - sum[slow]);
    }

    return ans;
}

const int B_MX = 1000;

ll brute() {
    ll ans = 0;
    for (dbl pos = 0; pos <= B_MX + 1; pos += 0.1) {
        ll cur = 0;
        for (int i=0; i<N; ++i) {
            bool ok = true;
            for (int j=0; j<M; ++j) {
                if (abs(pos - (i * 100)) >= abs((i * 100) - B[j])) ok = false;
            }
            if (ok) cur += A[i];
        }
        chmx(ans, cur);
    }
    return ans;
}

void test() {
    mt19937 rng(8);
    for (N=2; N<=9; N++) {
        for (M=1; M<=5; M++) {
            debug(N, M);
            for (int t=0; t<10000; ++t) {
                for (int i=0; i<N; ++i) {
                    A[i] = 1 + (rng() % 1000);
                }
                for (int i=0; i<M; ++i) {
                    B[i] = rng() % B_MX;
                }
                const ll bans = brute();
                const ll sans = solve();
                if (sans != bans) {
                    debug(sans, bans);
                    cout << N << ' ' << M << endl;
                    for (int i=0; i<N; ++i) {
                        if (i) cout << ' ';
                        cout << A[i];
                    } cout << endl;
                    for (int i=0; i<M; ++i) {
                        if (i) cout << ' ';
                        cout << B[i];
                    } cout << endl;
                    assert(sans == bans);
                }
            }
        }
    }
}

int main() {
    //test(); return 0;
    setIO();

    ll TEST_COUNT = 1;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N >> M;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        for (int i=0; i<M; ++i) {
            cin >> B[i];
        }
        cout << solve() << '\n';
    }

    return 0;
}

/*
2 1
1 100
100

2 1
1 100
101

2 1
1 100
50

3 1
1 10 100
100

3 1
1 10 100
101

3 1
1 10 100
201

5 1
1 10 100 1000 1000
300

5 1
1 10 100 1000 1000
301

3 3
1 1 1
0 100 200

5 5
1 1 1 1 1
1 99 101 199 201
*/
