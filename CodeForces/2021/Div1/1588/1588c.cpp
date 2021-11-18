//1588c.cpp created at 11/13/21 22:02:18
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

ll solve() {
    B[0] = A[0];
    for (int i=1; i<N; ++i) {
        B[i] = B[i-1];
        if (i & 1) B[i] -= A[i];
        else B[i] += A[i];
    }

    ll ans = 0;
    mll ct;
    for (int i=0; i<N; ++i) {
        ans += ct[B[i]];
        ++ct[B[i]];
        for (auto it = ct.begin(); it->fi < B[i]; it=ct.erase(it));
    }

    for (int i=0; i<N; ++i) {
        B[i] = -B[i];
    }
    ct.clear();
    for (int i=0; i<N; ++i) {
        ans += ct[B[i]];
        ++ct[B[i]];
        for (auto it = ct.begin(); it->fi < B[i]; it=ct.erase(it));
    }

    ll cur = 0;
    for (int i=0; i<N; ++i) {
        if (i && A[i-1] != A[i]) {
            cur = 0;
        }
        ++cur;
        ans -= (cur - 1) / 2;
    }

    return ans;
}

ll arr[MN];
bool check(const int i, const int j) {
    copy(A+i, A+j+1, arr);
    for (int a=0; a+i+1<=j; ++a) {
        arr[a+1] -= arr[a];
        if (arr[a+1] < 0) return false;
    }
    return arr[j-i] == 0;
}

ll brute() {
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        for (int j=i; j<N; ++j) {
            ans += check(i, j);
        }
    }
    return ans;
}

void test() {
    for (N=4; N<=10; ++N) {
        for (int t=0; t<=100000; ++t) {
            for (int i=0; i<N; ++i) {
                A[i] = rand() % 20;
                ll bans = brute();
                ll sans = solve();

                if (bans != sans) {
                    debug1(A, N);
                }
                assert(bans == sans);
            }
        }
    }
}

int main() {
    //test(); return 0;
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        cin >> N;
        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        cout << solve() << '\n';
    }

    return 0;
}
/*
4
1 0 0 1

16 15 17 18
7 0 0 0
*/
