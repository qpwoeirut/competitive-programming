//2124d.cpp created at 07/06/25 08:38:41
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

bool solve() {
    if (K <= 2) {
        return true;
    }

    copy(A, A+N, B);
    sort(B, B+N);
    ll kth = B[K - 2];

    M = 0;
    vector<int> fixed;
    for (int i=0; i<N; ++i) {
        if (A[i] < kth) fixed.pb(M);
        if (A[i] <= kth) B[M++] = A[i];
    }
    //debug(kth, fixed);
    //debug1(B, M);

    if (fixed.empty()) {
        return M >= K - 1;
    }
    
    int i = fixed[(fixed.size() - 1) / 2], j = fixed[fixed.size() / 2];
    int len = max(0, j - i - 1);
    //debug(i, j, len);
    while (0 <= i && j < M) {
        if (B[i] == B[j]) {
            len += 1 + (i < j);
            --i; ++j;
        } else if (B[i] == kth) --i;
        else if (B[j] == kth) ++j;
        else return false;
    }
    //debug(len);
    return len >= K - 1;
}

bool recurse(const vector<ll>& v) {
    bool palin = true;
    for (int i=0; i<v.size(); ++i) {
        palin &= v[i] == v[v.size() - i - 1];
    }
    if (palin) return true;

    for (int i=0; i<v.size(); ++i) {
        vector<ll> sub;
        for (int j=i+1; j<=v.size(); ++j) {
            sub.pb(v[j-1]);

            if (sub.size() >= K) {
                sort(all(sub));
                for (int k=i; k<j; ++k) {
                    if (v[k] == sub[K - 1]) {
                        vector<ll> cpy(all(v));
                        cpy.erase(cpy.begin() + k);
                        if (recurse(cpy)) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool brute() {
    vector<ll> v(A, A+N);
    return recurse(v);
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=8; ++N) {
        for (K=1; K<=N; ++K) {
            debug(N, K);
            for (int t=0; t<100000; ++t) {
                for (int i=0; i<N; ++i) A[i] = (rng() % N) + 1;

                bool sans = solve();
                bool bans = brute();
                if (sans != bans) {
                    cout << N << ' ' << K << '\n';
                    for (int i=0; i<N; ++i) cout << A[i] << ' ';
                    cout << '\n' << sans << ' ' << bans << endl;
                }
                assert(sans == bans);
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
        cin >> N >> K;
        for (int i=0; i<N; ++i) cin >> A[i];
    
        cout << (solve() ? "YES" : "NO") << '\n';;
    }

    return 0;
}
/*
1
4 4
2 2 4 3

1
4 4
4 4 3 4
*/
