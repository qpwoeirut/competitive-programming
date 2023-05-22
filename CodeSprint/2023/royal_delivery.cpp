//royal_delivery.cpp created at 05/21/23 11:32:33
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

ll P;
ll cost[10];

pll count_digits(ll x) {
    int digits = 0;
    ll p10 = 1;
    while (x > 0) {
        ++digits;
        x /= 10;
        p10 *= 10;
    }
    p10 /= 10;
    return pll(digits, p10);
}

ll solve() {
    ll ans = 0;
    for (int i=0; i<N; ++i) {
        pll p = count_digits(A[i]);
        ll digits = p.fi, p10 = p.se;
        ll ct = A[i], cur = P;
        for (int j=0; j<digits; ++j) {
            for (int d=0; d<10; ++d) {
                if (d * p10 <= ct) cost[d] = B[d] - d * p10 * P;
                else cost[d] = INF;
            }
            ll best = min_element(cost, cost+10) - cost;
            ct -= best * p10;
            cur += B[best];

            p10 /= 10;
        }

        cur += ct * P;

        ans += min(cur, A[i] * P);
    }
    return ans;
}


ll cost_of(ll x) {  // assumes B[i] is the cost of digit i
    ll cost = 0;
    while (x > 0) {
        cost += B[x % 10];
        x /= 10;
    }
    return cost;
}

const int MAX_X = 1000;
ll cache[MAX_X];
ll brute() {  // assumes N is defined and A[i] is the number of times the i_th character appears (value of character is ignored)
    for (int i=0; i<MAX_X; ++i) {
        cache[i] = i * P;
        for (int j=1; j<=i; ++j) {
            cache[i] = min(cache[i], cost_of(j) + P + cache[i - j]);
        }
    }

    ll ans = 0;
    for (int i=0; i<N; ++i) {
        assert(A[i] < MAX_X);
        ans += cache[A[i]];
    }
    return ans;
}

void test() {
    mt19937 rng(8);
    for (N=1; N<=10; ++N) {
        for (P=1; P<=10; ++P) {
            debug(N, P);
            for (int t=0; t<100000; ++t) {
                for (int i=0; i<N; ++i) {
                    A[i] = rng() % 20;
                }
                B[0] = 0;
                for (int i=1; i<10; ++i) {
                    B[i] = B[i-1] + (rng() % 4);
                }

                ll sans = solve();
                ll bans = brute();
                if (sans != bans) {
                    cout << N << ' ' << P << '\n';
                    for (int i=0; i<N; ++i) {
                        cout << A[i] << '\n';
                    }
                    for (int i=0; i<10; ++i) {
                        cout << B[i] << ' ';
                    }
                    cout << endl;
                    cout << sans << ' ' << bans << endl;
                }
                assert(sans == bans);
            }
        }
    }
}

int main() {
    setIO();

    //test(); return 0;

    cin >> N >> P;

    for (int i=0; i<N; ++i) {
        char c;
        cin >> c >> A[i];
    }
    for (int i=0; i<10; ++i) {
        cin >> B[i];
    }

    //cout << solve() << '\n';
    cout << brute() << '\n';

    return 0;
}
/*
1 0
A 100
0 1 1 1 1 1 1 1 1 1

1 1
A 100
0 1 1 1 1 1 1 1 1 1

1 1
A 100
0 0 9 9 9 9 9 9 9 9
*/
