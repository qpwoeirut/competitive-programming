//driving.cpp created at 08/06/22 11:53:41
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
ll ans[MN];
//ll G[MN][MN];
//set<pll> adj[MN];
string S, T;

struct Edge {
    int u, v, t;
};

Edge edge[MN];

multiset<int> cool_sz;
int cool[MN];
void merge(int i, int j) {
    cool_sz.erase(cool_sz.find(cool[i]));
    cool_sz.erase(cool_sz.find(cool[j]));
    cool_sz.insert(cool[i] + cool[j]);
    cool[i] += cool[j];
}
void add(int i, int x) {
    cool_sz.erase(cool_sz.find(cool[i]));
    cool_sz.insert(cool[i] + x);
    cool[i] += x;
}

int par[MN], sz[MN];
int root(const int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(int u, int v) {
    int ru = root(u), rv = root(v);
    if (ru == rv) return false;

    if (sz[ru] < sz[rv]) {
        swap(ru, rv);
        swap(u, v);
    }
    merge(ru, rv);
    sz[ru] += sz[rv];
    par[rv] = par[v] = ru;

    return true;
}

void solve(int testcase) {
    cin >> N >> M >> Q;
    for (int i=0; i<M; ++i) {
        cin >> edge[i].u >> edge[i].v >> edge[i].t;
        --edge[i].u; --edge[i].v;
    }
    for (int i=0; i<Q; ++i) {
        cin >> A[i];
        --A[i];
    }
    sort(edge, edge+M, [](const Edge& a, const Edge& b) {
        return a.t < b.t || (a.t == b.t && (a.u < b.u || (a.u == b.u && a.v < b.v)));
    });

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
        cool[i] = 0;
        cool_sz.insert(0);
    }
    for (int i=0; i<Q; ++i) {
        add(root(A[i]), 1);
    }

    int qi = Q-1;
    fill(ans, ans+Q, -1);
    for (int i=0; i<M && qi>0; ++i) {
        debug(i, qi);
        join(edge[i].u, edge[i].v);
        while (qi > 0 && *cool_sz.rbegin() > 1) {
            ans[qi] = edge[i].t;
            add(root(A[qi]), -1);
            --qi;
        }
    }

    for (int i=0; i<Q; ++i) {
        cout << ans[i] << '\n';
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
7 10 5
1 2 1
1 3 2
1 3 3
1 5 1
2 4 2
2 5 2
3 4 2
3 4 1
4 5 2
6 7 1
7
1
4
3
6
*/
