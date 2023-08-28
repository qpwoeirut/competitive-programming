//1578l.cpp created at 10/01/21 10:18:55

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
#define eb emplace_back
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
const int MN = 101001;
const int LG = 24;
const ll INF = 2e18 + 1;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
//set<ll> adj[MN];
string S, T;

struct Edge {
    int u, v;
    ll w;
    inline const bool operator<(const Edge& o) const {
        return w > o.w || (w == o.w && (u < o.u || (u == o.u && v < o.v)));
    }
    Edge() {
        u = v = w = 0;
    }
    Edge(const int _u, const int _v, const ll _w) {
        u = _u; v = _v; w = _w;
    }
};

ll total_width;
Edge edge[MN];
int size[MN];

int par[MN];
ll value[MN];
set<Edge> edges[MN];
int root(int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(int u, int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;
    if (edges[ru].size() < edges[rv].size()) swap(ru, rv);
    edges[ru].ins(all(edges[rv]));
    size[ru] += size[rv];
    par[rv] = par[u] = par[v] = par[ru];
    value[ru] += value[rv];
    return true;
}

void init_dsu() {
    for (int i=0; i<N; ++i) {
        par[i] = i;
        size[i] = 1;
        value[i] = A[i];
        edges[i].clear();
    }
    for (int i=0; i<M; ++i) {
        edges[edge[i].u].ins(edge[i]);
        edges[edge[i].v].ins(edge[i]);
    }
}

pll pq[MN];
int pq_sz;

bool check(const ll width) {
    init_dsu();

    pq_sz = 0;
    for (int i=0; i<N; ++i) {
        pq[pq_sz++] = pll(value[i], i);
        push_heap(pq, pq+pq_sz, greater<pll>());
    }
    while (pq_sz > 0) {
        pop_heap(pq, pq+pq_sz, greater<pll>());
        const pll p = pq[--pq_sz];
        if (root(p.se) != p.se || p.fi < value[p.se]) continue;

        bool change = false;
        for (auto it=edges[p.se].begin(); it!=edges[p.se].end(); it=edges[p.se].erase(it)) {
            if (width - p.fi <= it->w && join(it->u, it->v)) {
                change = true;
            }
            if (width - p.fi > it->w) break;
        }

        if (change) {
            pq[pq_sz++] = pll(value[root(p.se)], root(p.se));
            push_heap(pq, pq+pq_sz, greater<pll>());
            if (size(root(p.se) == N)) break;
        }
    }
    bool ok = true;
    for (int i=1; i<N; ++i) {
        ok &= root(i) == root(0);
    }
    return ok;
}

void solve(int testcase) {
    cin >> N >> M;
    total_width = 0;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        total_width += A[i];
    }
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        --edge[i].u; --edge[i].v;
    }

    if (check(1 + total_width) == false) {
        cout << -1 << '\n';
        return;
    }

    ll lo = 1, hi = INIT;
    while (lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if (check(mid + total_width)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << '\n';
}
        

int main() {
    setIO();
    
    ll TEST_COUNT = 1;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }
    
    return 0;
}
