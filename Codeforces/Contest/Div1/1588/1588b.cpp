//1588b.cpp created at 11/13/21 22:02:17
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
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

ll query(const int L, const int R) {
    if (L == R) return 0;
    cout << "? " << L+1 << ' ' << R+1 << endl;
    ll x = 0;
    //for (int i=L; i<=R; ++i) { for (int j=i+1; j<=R; ++j) { if (A[i] > A[j]) ++x; } }
    cin >> x;
    return x;
}

bool is_triangular(ll n) {
    n = n * 8 + 1;
    ll s = sqrt(n);
    return square(s) == n || square(s+1) == n;
}

ll f(ll n) {
    n = n * 8 + 1;
    ll s = sqrt(n);
    if (square(s) == n) return (s - 1) / 2;
    if (square(s+1) == n) return s / 2;
    assert(false);
}

ll ans_i, ans_j, ans_k;

void solve() {
    int L = 0, R = N;
    ans_i = -1;
    while (L < R) {
        int mid = (L + R + 1) / 2;
        const ll q = query(0, mid);
        //debug(L, mid, R, q);
        if (is_triangular(q) && q != 0) {
            //debug(mid, q, ans_i);
            if (ans_i == -1) {
                ans_i = mid - f(q);
                const ll q2 = query(0, mid - 1);
                if (!is_triangular(q2) || ans_i != mid - 1 - f(q2)) {
                    ans_i = -1;
                }
            }
        }
        if (q == 0 || (is_triangular(q) && ans_i != -1 && ans_i + f(q) == mid)) {
            L = mid;
        } else {
            R = mid - 1;
        }
    }

    ans_j = L + 1;
    //debug(ans_i, ans_j);
    ll total = query(0, N-1);

    ll ij_invs = (ans_j - ans_i) * (ans_j - ans_i - 1) / 2;
    ll jk_invs = total - ij_invs;
    //debug(ij_invs, jk_invs);
    assert(is_triangular(jk_invs));
    ans_k = ans_j + f(jk_invs);
}

void test() {
    for (N=4; N<=1000; ++N) {
        if ((N & 31) == 0) debug(N);
        for (int i=0; i<N; ++i) {
            for (int j=i+2; j<N; ++j) {
                for (int k=j+1; k<N; ++k) {
                    for (int a=0; a<N; ++a) A[a] = a+1;
                    reverse(A+i, A+j);
                    reverse(A+j, A+k+1);
                    solve();
                    assert(ans_i == i && ans_j == j && ans_k == k);
                }
            }
        }
    }
}

int main() {
    //test(); return 0;
    setIO();

    //for (ll i=1; i<=1e5; ++i) { for (ll j=i; j<=1e5; ++j) {
    //    ll x = i*(i+1)/2 + j*(j+1)/2;
    //    if (is_triangular(x)) { cout << i << ' ' << j << endl; } } }

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        solve();
        cout << "! " << ans_i+1 << ' ' << ans_j + 1 << ' ' << ans_k + 1 << endl;
    }

    return 0;
}
