//save_the_timeline.cpp created at 08/12/23 10:31:26
// finished code 7 minutes after contest ended
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
const ll MOD = 998244353; //1e9+9; //1e9+21; //1e9+33;
const int MN = 1001001;

ll N, M, K, Q;
ll A[MN];
ll B[MN];
//ll G[MN][MN];
vector<ll> adj[MN];
vector<ll> child[MN];
string S, T;

int tour_idx[MN][2];
void tour(int u, int par, int& n) {
    debug(u, n);
    tour_idx[u][0] = n++;
    for (int v: adj[u]) {
        if (v != par) tour(v, u, n);
    }
    debug(u, n, 1);
    tour_idx[u][1] = n++;
}

int parent[MN];
int depth[MN];
int cost[MN];
void dfs_depth(int u, int par) {
    if (u == 0) depth[u] = 0;
    parent[u] = par;

    cost[u] = INIT;
    for (int v: adj[u]) {
        if (v != par) {
            depth[v] = depth[u] + 1;
            child[u].pb(v);
            dfs_depth(v, u);
            chmn(cost[u], cost[v] + 1);
        }
    }
    if (cost[u] == INIT) cost[u] = 0;
    if (u == 0) cost[u] = 0;
}

ll dp[MN];
ll E[MN];
ll dfs_ans(int u, int par) {  // returns P(u and children not active)
    ll all_children_inactive = 1;
    for (int v: child[u]) {
        all_children_inactive = (all_children_inactive * dfs_ans(v, u)) % MOD;
    }
    all_children_inactive = (all_children_inactive + MOD) % MOD;
    dp[u] = (A[u] * all_children_inactive) % MOD;
    E[u] = (dp[u] * (depth[u] + cost[u])) % MOD;
    return ((1 - A[u]) * all_children_inactive) % MOD;
}

ll sub_E[MN];
void dfs_prop(int u, int par) {
    sub_E[u] = 0;
    for (int v: child[u]) {
        dfs_prop(v, u);
        sub_E[u] += E[v] + sub_E[v];
    }
    sub_E[u] %= MOD;
}

int incl[MN];
bool used[MN];
void solve(int testcase) {
    cin >> N >> Q;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
        adj[i].clear();
        child[i].clear();
    }
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v; --u; --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int node = 0;
    tour(0, -1, node);
    assert(node == 2*N);

    dfs_depth(0, -1);
    dfs_ans(0, -1);
    dfs_prop(0, -1);

    debug1(depth, N);
    debug1(cost, N);
    debug1(dp, N);
    debug1(E, N);
    debug1(sub_E, N);

    for (int q=0; q<Q; ++q) {
        fill(used, used+N, false);
        cin >> K;
        for (int i=0; i<K; ++i) {
            cin >> B[i]; --B[i];
        }
        sort(B, B+K, [](const int ia, const int ib) {
            //return tour_idx[ia][0] < tour_idx[ib][0];
            return depth[ia] > depth[ib] || (depth[ia] == depth[ib] && ia > ib);
        });

        ll ans = sub_E[0] + E[0];
        int ib = 0;
        int lo = 0, hi = 0;
        for (int d=depth[B[0]]; d>=0; --d) {
            for (; ib<K && depth[B[ib]] == d; ++ib) {
                if (!used[B[ib]]) {
                    used[B[ib]] = true;
                    incl[hi++] = B[ib];
                    ans += E[B[ib]] * binpow(A[B[ib]], MOD - 2, MOD) % MOD;
                    //debug(B[ib]);
                }
            }
            sort(incl+lo, incl+hi);
            //debug(lo, hi); debug1(incl, hi);

            int hi2 = hi;
            while (depth[incl[lo]] == d && lo < hi) {
                if (parent[incl[lo]] != -1 && !used[parent[incl[lo]]]) {
                    used[parent[incl[lo]]] = true;
                    incl[hi2++] = parent[incl[lo]];
                    debug(incl[lo], parent[incl[lo]]);
                }
                //debug(incl[lo], E[incl[lo]]);
                ans -= E[incl[lo++]];
                ans %= MOD;
            }
            hi = hi2;
            ans %= MOD;
        }
        ans = (ans + MOD) % MOD;
        cout << ans << '\n';
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
