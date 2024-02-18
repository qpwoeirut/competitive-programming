//hhpc1p3.cpp created at 01/31/24 20:22:03
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
const int MN = 5001;

struct Ridge {
    ll a, b;
    ll val;
};

ll N, M, K, Q;
Ridge A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

struct frac {
    ll numer, denom;

    frac(const ll n, const ll d) {
        ll g = gcd(n, d);
        if (n < 0 && d < 0 && g > 0) g = -g;
        numer = n / g;
        denom = d / g;
    }

    const bool operator<(const frac& o) const {
        return (__int128)(numer) * o.denom < (__int128)(denom) * o.numer;
    }
};

string to_string(frac f) {
    return to_string(f.numer) + "/" + to_string(f.denom);
}

vector<pair<frac, int>> falling[MN];
vector<pair<frac, int>> rising[MN];

vector<ll> fsum[MN];
vector<ll> rsum[MN];

ll above_sum[MN];

void solve(int testcase) {
    cin >> N >> M >> Q >> K;

    for (int i=0; i<N; ++i) {
        cin >> A[i].a >> A[i].b >> A[i].val;
    }

    for (int i=0; i<N; ++i) {
        for (int j=0; j<i; ++j) {
            if ((A[i].a >= A[j].a && A[i].b > A[j].b) || (A[i].a > A[j].a && A[i].b >= A[j].b)) {
                above_sum[j] += A[i].val;
            } else if ((A[j].a >= A[i].a && A[j].b > A[i].b) || (A[j].a > A[i].a && A[j].b >= A[i].b)) {
                above_sum[i] += A[j].val;
            } else if (A[i].a == A[j].a && A[i].b == A[j].b) {
                continue;
            } else {
                // a + x/m * (b - a) = c + x/m * (d - c)
                // x/m * (b - a + c - d) = c - a
                // x = m * (c - a) / (b - a + c - d)
                frac intersect(M * (A[j].a - A[i].a), A[i].b - A[i].a + A[j].a - A[j].b);

                if (A[i].a >= A[j].a) {
                    rising[i].eb(intersect, j);
                    falling[j].eb(intersect, i);
                } else {
                    falling[i].eb(intersect, j);
                    rising[j].eb(intersect, i);
                }
            }
        }
    }

    for (int i=0; i<N; ++i) {
        sort(all(falling[i]));
        sort(all(rising[i]));

        fsum[i] = vector<ll>(falling[i].size() + 1);
        for (int j=1; j<fsum[i].size(); ++j) {
            fsum[i][j] = fsum[i][j - 1] + A[falling[i][j - 1].se].val;
        }

        rsum[i] = vector<ll>(rising[i].size() + 1);
        for (int j=1; j<rsum[i].size(); ++j) {
            rsum[i][j] = rsum[i][j - 1] + A[rising[i][j - 1].se].val;
        }
    }

    for (int i=0; i<Q; ++i) {
        int s, p;
        cin >> p >> s; --p;

        const int L = s;
        const int R = s + K;

        int left_rising = LB(all(rising[p]), make_pair(frac(R, 1), -1)) - rising[p].begin();
        debug(left_rising, rsum[p], p);
        ll left_sum = rsum[p][left_rising];

        int right_falling = LB(all(falling[p]), make_pair(frac(L, 1), (int)N)) - falling[p].begin();
        ll right_sum = fsum[p].back() - fsum[p][right_falling];

        ll ans = above_sum[p] + left_sum + right_sum;
        debug(rising[p], falling[p]);
        debug(left_rising, right_falling);
        debug(above_sum[p], left_sum, right_sum);

        cout << ans << '\n';
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
4 100 5 25
10 10 1
12 12 2
14 6 4
6 14 8
3 25
3 50
4 25
4 50
2 0

2 100 1 25
12 12 1
14 6 2
2 25

5 1000000000 5 1000000000
-1000000000 1000000000 1000000000
-1000000000 -1000000000 100000000
1000000000 -1000000000 1000000000
1000000000 1000000000 1000000000
0 0 1000000
1 0
2 0
3 0
4 0
5 0

5 100 1 100
-10 10 1000000
-10 -10 100000
10 -10 10000
10 10 1000
0 0 10
4 0
*/
