//beaverland.cpp created at 04/06/25 08:34:38
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
set<ll> adj[MN];
string S, T;

ll dist[MN];

void add_edge(vector<pll>& added, int u, int v) {
    if (u == v) return;
    if (adj[u].count(v)) {
        assert(adj[v].count(u));
        return;
    }
    adj[u].insert(v);
    adj[v].insert(u);
    added.emplace_back(u + 1, v + 1);
}

void solve(int testcase) {
    cin >> N >> M >> K;
    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }
    for (int i=0; i<K; ++i) {
        cin >> A[i]; --A[i];
    }
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v; --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    
    vector<pll> added;
    add_edge(added, 0, A[0]);
    for (int i=0; i+1<K; ++i) {
        add_edge(added, A[i], A[i+1]);
    }
    debug1(adj, N);

    fill(dist, dist+N, INF);
    dist[0] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.emplace(0, 0);
    while (pq.size() > 0) {
        const pll cur = pq.top(); pq.pop();
        debug(cur);
        const int u = cur.se;
        if (dist[u] < cur.fi) continue;

        for (int v: adj[u]) {
            if (chmn(dist[v], dist[u] + 1)) {
                pq.emplace(dist[v], v);
            }
        }
    }

    for (int i=0; i+1<K; ++i) {
        debug(dist[A[i]], dist[A[i+1]]);
        if (dist[A[i]] >= dist[A[i+1]]) {
            cout << "-1\n";
            return;
        }
    }
    cout << added.size() << '\n';
    for (const pll& p: added) {
        cout << p.fi << ' ' << p.se << '\n';
    }
}

int main() {
    setIO();

    ll TEST_COUNT = 1;
    cin >> TEST_COUNT;

    for (int test_case=1; test_case<=TEST_COUNT; ++test_case) {
        solve(test_case);
    }

    return 0;
}
/*
2
6 7 1
1
1 2
1 3
3 4
1 5
5 6
6 7
7 8

6 7 2
2 4
1 2
1 3
3 4
1 5
5 6
6 7
7 8
*/
