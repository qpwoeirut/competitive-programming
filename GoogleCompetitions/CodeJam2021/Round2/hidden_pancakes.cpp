//hidden_pancakes.cpp created at 05/15/21 07:47:05

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
set<ll> adj[MN];
string S, T;

ll par[MN];
ll fact[MN], inv[MN];
ll dp[MN], sub_sz[MN];

// https://discuss.codechef.com/t/maxtopo-editorial/86587
void get_topo_count(int u) {
    dp[u] = 1;
    sub_sz[u] = 1;

    for (const ll v: adj[u]) {
        get_topo_count(v);
        dp[u] = (dp[u] * dp[v]) % MOD;
        dp[u] = (dp[u] * inv[sub_sz[v]]) % MOD;
        sub_sz[u] += sub_sz[v];
    }
    dp[u] = (dp[u] * fact[sub_sz[u] - 1]) % MOD;
}

ll choose(const ll n, const ll k) {
    return (((fact[n] * inv[k]) % MOD) * inv[n-k]) % MOD;
}

void solve(int testcase) {
    cin >> N;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        adj[i].clear();
    }
    fill(par, par+N, -1);
    if (A[0] != 1) {
        cout << "Case #" << testcase << ": 0" << '\n';
        return;
    }

    vector<int> st;
    st.pb(0);
    for (int i=1; i<N; ++i) {
        debug(i, st, A[i-1] - A[i] + 1);
        if (A[i-1] + 1 < A[i]) {
            cout << "Case #" << testcase << ": 0" << '\n';
            return;
        }
        set<int> replaced;
        for (int j=0; j<A[i-1] - A[i] + 1; ++j) {
            replaced.ins(st.back());
            st.pop_back();
        }
        for (const int j: replaced) {
            if (replaced.count(par[j]) == 0) {
                par[j] = i;
            }
        }
        if (st.size() > 0) {
            par[i] = st.back();
        }
        st.pb(i);
    }

    ll u = -1;
    for (int i=0; i<N; ++i) {
        if (par[i] == -1) {
            if (u != -1) {
                cout << "Case #" << testcase << ": 0" << '\n';
                return;
            }
            u = i;
        } else {
            adj[par[i]].ins(i);
        }
    }

    debug1(par, N);
    debug1(adj, N);
    debug(u);

    get_topo_count(u);

    cout << "Case #" << testcase << ": " << dp[u] << '\n';
}
        

int main() {
    setIO();

    fact[0] = inv[0] = 1;
    for (int i=1; i<MN; ++i) {
        fact[i] = fact[i-1] * i % MOD;
        inv[i] = binpow(fact[i], MOD-2, MOD);
    }
    
    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
/*
1
5
2 1 1 1 1
*/
