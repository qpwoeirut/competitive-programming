//1975e.cpp created at 05/25/24 08:51:31
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
vector<ll> adj[MN];
string S, T;

int par[MN];
int depth[MN];
void dfs(int u, int d=0) {
    depth[u] = d;
    for (int x: adj[u]) {
        if (x != par[u]) {
            par[x] = u;
            dfs(x, d + 1);
        }
    }
}

int ct[MN];
void solve(int testcase) {
    cin >> N >> Q;
    A[0] = 0;
    for (int i=1; i<=N; ++i) {
        cin >> A[i];
        adj[i].clear();
    }
    for (int i=1; i<N; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }

    fill(ct, ct + N + 1, 0);
    fill(par, par + N + 1, 0);
    dfs(1);

    set<pll> on;
    for (int i=1; i<=N; ++i) {
        if (A[i]) {
            ++ct[par[i]];
            on.emplace(depth[i], i);
        }
    }

    multiset<int> cts[2];
    for (int i=0; i<=N; ++i) {
        cts[A[i]].insert(ct[i]);
    }

    for (int q=0; q<Q; ++q) {
        int u;
        cin >> u;

        cts[A[u]].erase(cts[A[u]].find(ct[u]));
        A[u] ^= 1;
        cts[A[u]].insert(ct[u]);

        const int p = par[u];
        cts[A[p]].erase(cts[A[p]].find(ct[p]));
        if (A[u]) {
            cts[A[p]].insert(++ct[p]);
            on.emplace(depth[u], u);
        } else {
            cts[A[p]].insert(--ct[p]);
            on.erase(pll(depth[u], u));
        }

        if (cts[1].empty()) {
            cout << "NO\n";
            continue;
        }
        if (cts[1].size() == 1) {
            cout << "YES\n";
            continue;
        }

        auto it = cts[0].rbegin();
        auto it2 = it; ++it2;
        const bool connected = *it == 1 && (it2 == cts[0].rend() || *it2 == 0);
        debug(*it, *it2);

        it = cts[1].rbegin();
        it2 = it; ++it2;
        const bool chain = *it == 1 || (*it == 2 && *it2 <= 1 && ct[on.begin()->se] == 2);

        debug(on, connected, chain);
        debug(*it, *it2);
        debug(cts[0], cts[1]);

        cout << (connected && chain ? "YES\n" : "NO\n");
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
8 11
0 0 0 0 0 0 0 0
1 2
2 3
3 4
2 5
5 6
6 7
6 8
6
6
7
6
8
5
8
3
4
2
1

YES
NO
YES
YES
YES
NO
YES
NO
NO
YES
NO
*/

/*
8 15
0 0 0 0 0 1 1 0
1 2
2 3
3 4
2 5
5 6
6 7
6 8
8
6
7
1
2
5
6
3
7
4
8
1
3
4
1

YES
NO
YES
NO
NO
NO
YES
NO
NO
NO
NO
YES
NO
YES
YES

1 2
0
1
1

2 3
1 0
1 2
1
1
2

3 5
1 1 0
1 2
1 3
3
1
2
2
1
*/
