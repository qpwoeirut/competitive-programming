//1508c.cpp created at 04/16/21 08:14:41

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

struct Edge {
    int u, v;
    ll w;

    inline bool operator<(const Edge& o) const {
        return w < o.w || (w == o.w && (u < o.u || (u == o.u && v < o.v)));
    }
};

ll N, M, K, Q;
ll A[MN], B[MN];
//ll G[MN][MN];
mll adj[MN];
set<ll> adj2[MN];
string S, T;

Edge edge[MN];

int par[MN], sz[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(const int u, const int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;

    if (sz[ru] < sz[rv]) swap(ru, rv);
    sz[ru] += sz[rv];
    par[u] = par[v] = par[rv] = ru;
    return true;
}
void init_dsu() {
    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
}

bool visited[MN];
bool cycle(const int u, const int par=-1) {
    if (visited[u]) return true;
    visited[u] = true;
    for (const int v: adj2[u]) {
        if (v != par) {
            if (cycle(v, u)) return true;
        }
    }
    return false;
}

ll kruskal(const int eu, const int ev, const ll ew) {
    init_dsu();
    for (int u=0; u<N; ++u) {
        for (const int v: adj2[u]) {
            if ((eu == u && ev == v) || (eu == v && ev == u)) continue;
            join(u, v);
        }
    }

    bool extra_used = false;
    ll ans = 0;
    for (int i=0; i<M; ++i) {
        if (!extra_used && edge[i].w > ew) {
            extra_used = true;
            if (join(eu, ev)) ans += ew;
        }
        if (join(edge[i].u, edge[i].v)) ans += edge[i].w;
        if (sz[root(edge[i].u)] == N) break;
    }

    return ans;
}

void solve(int testcase) {
    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        --edge[i].u; --edge[i].v;

        adj[edge[i].u][edge[i].v] = edge[i].w;
        adj[edge[i].v][edge[i].u] = edge[i].w;
    }
    sort(edge, edge+M);

    const ll m = ((N * (N-1)) >> 1) - M;
    if (m < N) {
        assert(N <= 700);
        for (int i=0; i<N; ++i) {
            for (int j=i+1; j<N; ++j) {
                if (adj[i].count(j) == 0) {
                    adj2[i].ins(j);
                    adj2[j].ins(i);
                }
            }
        }
        bool has_cycle = false;
        for (int i=0; i<N; ++i) {
            if (!visited[i]) has_cycle |= cycle(i);
        }

        debug(has_cycle);
        if (!has_cycle) {
            ll ans = INF;
            ll xsum = 0;
            for (int i=0; i<M; ++i) {
                xsum ^= edge[i].w;
            }
            debug(xsum);

            for (int u=0; u<N; ++u) {
                for (const int v: adj2[u]) {
                    chmn(ans, kruskal(u, v, xsum));
                }
            }
            cout << ans << '\n';
            return;
        }
    }

    int didx = min_element(adj, adj+N, [](const mll& a, const mll& b) {return sz(a) < sz(b);}) - adj;
    debug(didx);
    
    auto it = adj[didx].begin();
    init_dsu();
    for (int j=0; j<N; ++j) {
        if (it == adj[didx].end() || j != it->fi) {
            join(didx, j);
        } else ++it;
    }

    vector<int> out;
    for (int i=0; i<N; ++i) {
        if (root(i) != root(didx)) out.pb(i);
    }
    assert(sz(out) <= 700);

    for (int i=0; i<N; ++i) {
        for (const int j: out) {
            if (adj[i].count(j) == 0) {
                join(i, j);
            }
        }
        if (sz[root(i)] == N) break;
    }
    debug1(par, N);

    ll ans = 0;
    for (int i=0; i<M; ++i) {
        if (join(edge[i].u, edge[i].v)) ans += edge[i].w;
    }

    cout << ans << '\n';
}
        

int main() {
    //ll mx = 2;
    //for (ll i=2; i<=200000; ++i) { if (i*(i-1)/2 <= 200000 + i-1) mx = i; }
    //debug(mx);

    setIO();
    
    ll TEST_COUNT = 1;
    
    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
